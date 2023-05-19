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

uint8_t detect_page_entry_type(Page_Entry_t *pe) {
    return pe->avl2;
}

Page_Entry_t *map_4kb_page(uint64_t phys_addr, uint64_t vaddr, uint8_t pe_flags) {
    translated_vaddr_t idcs = get_vaddr_indices(vaddr);
    uint16_t PML4i = idcs.PML4i;
    uint16_t PDPTi = idcs.PDPTi;
    uint16_t PDi = idcs.PDi;
    uint16_t PTi = idcs.PTi;

    PDPT_t PDPT;
    Page_Directory_t PD;
    Page_Table_t PT;

    Page_Entry_t *PML4e = &PML4T[PML4i];
    PML4e->reserved = 0;
    PML4e->xd = 0;
    if (PML4e->phys & PE_PRESENT)
        PDPT = (Page_Entry_t*)(PML4e->phys ALIGNED_4KB);
    else {
        PDPT = (PDPT_t)pmm_alloc_page();
        PML4e->phys = (uint64_t)PDPT;
    }
    PML4e->phys |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;

    Page_Entry_t *PDPTe = &PDPT[PDPTi];
    PDPTe->reserved = 0;
    PDPTe->xd = 0;
    if (PDPTe->phys & PE_PRESENT)
        PD = (Page_Entry_t*)(PDPTe->phys ALIGNED_4KB);
    else {
        PD = (Page_Directory_t)pmm_alloc_page();
        PDPTe->phys = (uint64_t)PD;
    }
    PDPTe->phys |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;

    Page_Entry_t *PDe = &PD[PDi];
    PDe->reserved = 0;
    PDe->xd = 0;
    if (PDe->phys & PE_PRESENT)
        PT = (Page_Entry_t*)(PDe->phys ALIGNED_4KB);
    else {
        PT = (Page_Directory_t)pmm_alloc_page();
        PDe->phys = (uint64_t)PD;
    }
    PDe->phys |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;

    Page_Entry_t *PTe = &PT[PTi];
    PDPTe->reserved = 0;
    PDPTe->xd = 0;
    PTe->phys = (uint64_t)phys_addr;
    PTe->phys |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;

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
    PML4e->reserved = 0;
    PML4e->xd = 0;
    if (PML4e->phys & PE_PRESENT)
        PDPT = (Page_Entry_t*)(PML4e->phys ALIGNED_4KB);
    else {
        PDPT = (PDPT_t)pmm_alloc_page();
        PML4e->phys = (uint64_t)PDPT;
    }
    PML4e->phys |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;

    Page_Entry_t *PDPTe = &PDPT[PDPTi];
    PDPTe->reserved = 0;
    PDPTe->xd = 0;
    if (PDPTe->phys & PE_PRESENT)
        PD = (Page_Entry_t*)(PDPTe->phys ALIGNED_4KB);
    else {
        PD = (Page_Directory_t)pmm_alloc_page();
        PDPTe->phys = (uint64_t)PD;
    }
    PDPTe->phys |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;

    Page_Entry_t *PDe = &PD[PDi];
    PDe->reserved = 0;
    PDe->xd = 0;
    PDe->phys = phys_addr;
    PDe->phys |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR | PE_SIZE;

    return PDe;
}

void setup_all_paging_structures() {
    // alloc a page frame for PML4
    PML4T = (Page_Entry_t*)pmm_alloc_page();
    memset(PML4T, 0, sizeof(Paging_Structure_t));

    // PDPT Setup
    for (int PML4Ti=0; PML4Ti<512; PML4Ti++) {
        PML4T[PML4Ti].phys |= PE_READ_WRITE | PE_USER_SUPERVISOR;
        PML4T[PML4Ti].xd = 0;
        PML4T[PML4Ti].reserved = 0;
    }
}

void setup_default_mapping() {
    kernel_address_response = *(kernel_address_request.response);
    hhdm_response = *(hhdm_request.response);

    uint64_t kernel_vbase = kernel_address_response.virtual_base;
    uint64_t kernel_pbase = kernel_address_response.physical_base;
    uint64_t hhdm_offset = hhdm_response.offset;

    // Map all physical memory to higher half and identity map
    for (uint64_t offset = 0; offset < 0x100000000; offset += PD_PAGE_SIZE) {
        map_2mb_page(offset, hhdm_offset + offset, 0);
        map_2mb_page(offset, offset, 0);
    }

    // printd(kernel_pbase);
    // printd(kernel_vbase);

    // Map the kernel
    for (uint64_t offset = 0; offset < (1<<30); offset += PD_PAGE_SIZE){
        map_2mb_page(kernel_pbase + offset, kernel_vbase + offset, 0);
    }

    // get the PML4i for the hhdm and kernel virtual addresses and set to present
    // i'm not using get_vaddr_indices for this
    // uint64_t hhdm_pml4i = ((*(hhdm_request.response)).offset >> 39) & 0x1ff;
    // uint64_t kernel_pml4i = ((*(kernel_address_request.response)).virtual_base >> 39) & 0x1ff;
}

void initialize_paging() {
	MAXPHYADDR = get_MAXPHYADDR();
	setup_all_paging_structures();
    setup_default_mapping();

    //construct the cr3
    uint64_t cr3 = (uint64_t)PML4T;
    // uint64_t cr3 = 0x530000;
    println();
    printd((uint64_t)PML4T);
    // printd(cr3);
    __asm__ volatile ("mov %0, %%cr3" : : "a"(cr3));
}
