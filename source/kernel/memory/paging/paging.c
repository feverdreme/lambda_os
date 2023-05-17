#include "paging.h"

#include <stdbool.h>
#include <memory/paging/virtm.h>
#include <limine_requests.h>
#include <arch/cpuid_query.h>

Full_Paging_Structure_t *FULL_PAGING_STRUCTURE;

int MAXPHYADDR;

struct limine_kernel_address_response kernel_address_response;
struct limine_hhdm_response hhdm_response;

Page_Entry_t *map_4kb_page(void *phys_addr, void *vaddr, uint8_t pe_flags) {
    // TODO: check to make sure 1GB mapping doesn't exist in PDPTe


    // FIXME: use PMM
    Page_Entry_t *pte = locate_page_entry(vaddr);

	pte->phys = (uint64_t)(phys_addr);
	pte->phys |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR | pe_flags;

	return pte;
}

Page_Entry_t *map_2mb_page(void *phys_addr, void *vaddr, uint8_t flags) {
    // TODO: USE DIFFERNET FUNCTION
    translated_vaddr_ptrs_t ptrs = get_vaddr_paging_ptrs(vaddr);

    Page_Entry_t *pde = ptrs.PDe;

    pde->phys = (uint64_t)(phys_addr) << PD_ADDRESS_BITSHIFT;
    pde->phys |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR | PE_SIZE | flags;
    pde->reserved = 0;
    pde->xd = 1;
    
    return pde;
}

Page_Entry_t *map_1gb_page(void *phys_addr, void *vaddr, uint8_t flags) {
    translated_vaddr_ptrs_t ptrs = get_vaddr_paging_ptrs(vaddr);

    Page_Entry_t *pdpte = ptrs.PDPTe;

    pdpte->phys = (uint64_t)(phys_addr) << PDPT_ADDRESS_BITSHIFT;
    pdpte->phys |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR | PE_SIZE | flags;
    pdpte->reserved = 0;
    pdpte->xd = 0;

    return pdpte;
}

// FIXME: DOESNT WORK
Page_Entry_t *enable_page_entry(void *vaddr) {
	translated_vaddr_ptrs_t ptrs = get_vaddr_paging_ptrs(vaddr);

	Page_Entry_t *pml4te = ptrs.PML4Te;
	Page_Entry_t *pdpte = ptrs.PDPTe;
	Page_Entry_t *pde = ptrs.PDe;
	Page_Entry_t *pte = ptrs.PTe;

	pml4te->phys |= PE_PRESENT;
	pdpte->phys |= PE_PRESENT;
	pde->phys |= PE_PRESENT;
	pte->phys |= PE_PRESENT;

	return pte;
}

Page_Entry_t *disable_page_entry(void *vaddr) {
    Page_Entry_t *pte = locate_page_entry(vaddr);
    pte->phys &= ~0x1; // set to non present

    return pte;
}

Page_Entry_t *locate_page_entry(void *vaddr) {
    // TODO: add checks that this page entry is actually enabled. there might not be a direct mapping to this because a higher structure doesnt point to this
    translated_vaddr_t idcs = get_vaddr_indices(vaddr);

    return &(FULL_PAGING_STRUCTURE->ALL_PT)[idcs.PML4i][idcs.PDPTi][idcs.PDi][idcs.PTi];
}

void setup_all_paging_structures() {
    // TODO: IDENTITY MAP FIRST 4 GiB

    FULL_PAGING_STRUCTURE = (Full_Paging_Structure_t*)PAGING_PHYS_ADDRESS;

    // set all PML4Te to not present and correct physical address
    for (int PML4Ti=0; PML4Ti<512; PML4Ti++) {
        Page_Entry_t *pe = &FULL_PAGING_STRUCTURE->PML4T[PML4Ti];

        pe->phys = (uint64_t)(PAGING_PHYS_ADDRESS) + sizeof(PML4_t) + PML4Ti * sizeof(PDPT_t);
        pe->phys |= PE_PRESENT | PE_READ_WRITE | PE_USER_SUPERVISOR;
        pe->reserved = 0;
        pe->xd = 0;
    }
}

void setup_default_mapping() {
    kernel_address_response = *(kernel_address_request.response);

    hhdm_response = *(hhdm_request.response);
    uint64_t hhdm_offset = hhdm_response.offset;

    // printd(kernel_address_response.physical_base);
    // printd(hhdm_offset);

    // Map all physical memory to higher half and identity map
    for (uint64_t offset = 0; offset < 4 * PDPT_PAGE_SIZE; offset += PDPT_PAGE_SIZE) {
        map_1gb_page((void*)offset, (void*)(hhdm_offset + offset), 0);
        map_1gb_page((void*)offset, (void*)offset, 0);
    }

    // Map the kernel
    map_1gb_page((void *)kernel_address_response.physical_base, (void *)kernel_address_response.virtual_base, 0);

    // get the PML4i for the hhdm and kernel virtual addresses and set to present
    // i'm not using get_vaddr_indices for this
    uint64_t hhdm_pml4i = ((*(hhdm_request.response)).offset >> 39) & 0x1ff;
    uint64_t kernel_pml4i = ((*(kernel_address_request.response)).virtual_base >> 39) & 0x1ff;

    FULL_PAGING_STRUCTURE->PML4T[hhdm_pml4i].phys |= PE_PRESENT;
    FULL_PAGING_STRUCTURE->PML4T[kernel_pml4i].phys |= PE_PRESENT;
    FULL_PAGING_STRUCTURE->PML4T[0].phys |= PE_PRESENT;
}

void initialize_paging() {
	MAXPHYADDR = get_MAXPHYADDR();
	setup_all_paging_structures();
    setup_default_mapping();

    //construct the cr3
    uint64_t cr3 = (PAGING_PHYS_ADDRESS);
    __asm__ volatile ("mov %0, %%cr3" : : "r"(cr3));
}
