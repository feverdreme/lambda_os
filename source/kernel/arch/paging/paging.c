#include "paging.h"

#include <arch/paging/virtm.h>

PML4_t 				*PML4T;
Contiguous_PDPT_t 	*ALL_PDPT;
Contiguous_PD_t 	*ALL_PD;
Contiguous_PT_t 	*ALL_PT;

int MAXPHYADDR;

/*
    Paging Structures Memory Layout for Quick Translation

    PML4 Table
    512 PDP Tables
    512 * 512 Page Directories
    512 * 512 * 512 Page Tables
*/

Page_Entry_t *set_page(void *phys_addr, void *vaddr, uint8_t pe_flags) {
    Page_Entry_t *pte = locate_page_entry(vaddr);

	pte->phys = phys_addr;
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

void setup_all_paging_structures() {}

void initialize_paging() {
	MAXPHYADDR = get_MAXPHYADDR();
	setup_all_paging_structures();
}
