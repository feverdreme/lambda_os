#include "paging.h"

#include <stdbool.h>
#include <arch/paging/virtm.h>
#include <limine_requests.h>
#include <arch/cpuid_query.h>

PML4_t 				*PML4T;
Contiguous_PDPT_t 	*ALL_PDPT;
Contiguous_PD_t 	*ALL_PD;
Contiguous_PT_t 	*ALL_PT;

int MAXPHYADDR;
struct limine_kernel_address_response kernel_address_response;

uint8_t detect_page_entry_type(Page_Entry_t *pe) {
    // detect what type
    int pe_type;

    // THIS ASSUME THIS IS SIGNED
    if ((int64_t)pe >= (int64_t)ALL_PT) 
        pe_type = PE_PTE_TYPE;
    else if ((int64_t)pe >= (int64_t)ALL_PD)
        pe_type = PE_PDE_TYPE;
    else if ((int64_t)pe >= (int64_t)ALL_PDPT)
        pe_type = PE_PDPTE_TYPE;
    else
        pe_type = PE_PML4E_TYPE;
    
    bool is_present = pe->present;
    bool maps_to_page = pe->reserved;

    return pe_type + (maps_to_page<<5) + (is_present<<6);
}

Page_Entry_t *map_4kb_page(void *phys_addr, void *vaddr, uint8_t pe_flags) {
    // TODO: check to make sure 1GB mapping doesn't exist in PDPTe

    Page_Entry_t *pte = locate_page_entry(vaddr);

	pte->phys = (uint64_t)(phys_addr);
	pte->flags = pe_flags;

	return pte;
}

Page_Entry_t *enable_page_entry(void *vaddr) {
	translated_vaddr_ptrs_t ptrs = get_vaddr_paging_ptrs(vaddr);

	Page_Entry_t *pml4te = ptrs.PML4Te;
	Page_Entry_t *pdpte = ptrs.PDPTe;
	Page_Entry_t *pde = ptrs.PDe;
	Page_Entry_t *pte = ptrs.PTe;

	pml4te->present = 1;
	pdpte->present = 1;
	pde->present = 1;
	pte->present = 1;

	return pte;
}

Page_Entry_t *disable_page_entry(void *vaddr) {
    Page_Entry_t *pte = locate_page_entry(vaddr);
    pte->present = 0;

    return pte;
}

Page_Entry_t *locate_page_entry(void *vaddr) {
    translated_vaddr_t idcs = get_vaddr_indices(vaddr);

    return &(*ALL_PT)[idcs.PML4i][idcs.PDPTi][idcs.PDi][idcs.PTi];
}

void setup_all_paging_structures() {
    // (signed)vaddr = (signed)paddr + offset
    kernel_address_response = *(kernel_address_request.response);
    
    uint64_t addr_offset = kernel_address_response.virtual_base - kernel_address_response.physical_base;

    // Map all physical memory
}

void initialize_paging() {
	MAXPHYADDR = get_MAXPHYADDR();
	setup_all_paging_structures();
}
