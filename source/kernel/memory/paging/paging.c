#include "paging.h"

#include <stdbool.h>
#include <memory/paging/virtm.h>
#include <limine_requests.h>
#include <arch/cpuid_query.h>
#include <memory/pmm/pmm.h>
#include <memory/mem.h>

Page_Entry_t* PML4T;

int MAXPHYADDR;

struct limine_kernel_address_response kernel_address_response;
struct limine_hhdm_response hhdm_response;

Page_Entry_t edit_entry(Page_Entry_t *pe, uint64_t phys_addr, uint8_t flags) {
    if (phys_addr % 0x1000 != 0)
        kpanic("PAGING ERROR: PHYSICAL ADDRESS NOT ALIGNED");
    
    *pe = phys_addr | flags;
    return *pe;
}

uint64_t next_aligned_addr(uint64_t addr, uint64_t alignment) {
    return alignment * (addr / alignment + 1);
}

Page_Entry_t *map_4kb_page(uint64_t phys_addr, uint64_t vaddr, uint8_t flags) {
    translated_vaddr_t idcs = get_vaddr_indices(vaddr);
    uint16_t PML4i = idcs.PML4i;
    uint16_t PDPTi = idcs.PDPTi;
    uint16_t PDi = idcs.PDi;
    uint16_t PTi = idcs.PTi;

    PDPT_t PDPT;
    Page_Directory_t PD;
    Page_Table_t PT;

    Page_Entry_t *PML4e = &PML4T[PML4i];
    if (*PML4e & PE_PRESENT)
        PDPT = (Page_Entry_t*)(*PML4e ALIGNED_4KB);
    else {
        PDPT = (PDPT_t)pmm_alloc_page();
        *PML4e = (uint64_t)PDPT;
    }
    *PML4e |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;

    Page_Entry_t *PDPTe = &PDPT[PDPTi];
    if (*PDPTe & PE_PRESENT)
        PD = (Page_Entry_t*)(*PDPTe ALIGNED_4KB);
    else {
        PD = (Page_Directory_t)pmm_alloc_page();
        *PDPTe = (uint64_t)PD;
    }
    *PDPTe |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;

    Page_Entry_t *PDe = &PD[PDi];
    if (*PDe & PE_PRESENT)
        PT = (Page_Entry_t*)(*PDe ALIGNED_4KB);
    else {
        PT = (Page_Entry_t*)pmm_alloc_page();
        *PDe = (uint64_t)PT;
    }
    *PDe |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;

    Page_Entry_t *PTe = &PT[PTi];
    *PTe = phys_addr;
    *PTe |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;

    return PTe;
}

Page_Entry_t *map_2mb_page(uint64_t phys_addr, uint64_t vaddr, uint8_t flags) {
    translated_vaddr_t idcs = get_vaddr_indices(vaddr);
    uint16_t PML4i = idcs.PML4i;
    uint16_t PDPTi = idcs.PDPTi;
    uint16_t PDi = idcs.PDi;

    PDPT_t PDPT;
    Page_Directory_t PD;

    Page_Entry_t *PML4e = &PML4T[PML4i];
    if (*PML4e & PE_PRESENT)
        PDPT = (Page_Entry_t*)(*PML4e ALIGNED_4KB);
    else {
        PDPT = (PDPT_t)pmm_alloc_page();
        *PML4e = (uint64_t)PDPT;
    }
    *PML4e |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;

    Page_Entry_t *PDPTe = &PDPT[PDPTi];
    if (*PDPTe & PE_PRESENT)
        PD = (Page_Entry_t*)(*PDPTe ALIGNED_4KB);
    else {
        PD = (Page_Directory_t)pmm_alloc_page();
        *PDPTe = (uint64_t)PD;
    }
    *PDPTe |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;

    Page_Entry_t *PDe = &PD[PDi];
    *PDe = phys_addr;
    *PDe |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR | PE_SIZE;

    return PDe;
}

void setup_all_paging_structures() {
    // alloc a page frame for PML4
    PML4T = (Page_Entry_t*)pmm_alloc_page();
    memset(PML4T, 0, sizeof(Paging_Structure_t));
}

void setup_default_mapping() {
    kernel_address_response = *(kernel_address_request.response);
    hhdm_response = *(hhdm_request.response);

    uint64_t kernel_vbase = kernel_address_response.virtual_base;
    uint64_t kernel_pbase = kernel_address_response.physical_base;
    uint64_t hhdm_offset = hhdm_response.offset;

    // Identity map and Higher Half map
    for (uint64_t offset = 0; offset < (4ULL << 30); offset += PD_PAGE_SIZE) {
        map_2mb_page(offset, hhdm_offset + offset, 0);
        map_2mb_page(offset, offset, 0);
    }

    printh(kernel_pbase);
    println();
    printh(kernel_vbase);
    println();

    // Map the unaligned kernel address base
    for (uint64_t offset=0; offset < PT_PAGE_SIZE * 100; offset += PT_PAGE_SIZE){
        map_4kb_page(kernel_pbase + offset, kernel_vbase + offset, 0);
    }
}

void initialize_paging() {
	MAXPHYADDR = get_MAXPHYADDR();
	setup_all_paging_structures();
    setup_default_mapping();

    //construct the cr3
    uint64_t cr3 = (uint64_t)PML4T;
    __asm__ volatile ("mov %0, %%cr3" : : "a"(cr3));
}
