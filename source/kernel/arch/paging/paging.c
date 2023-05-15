#include "paging.h"

#include <arch/paging/virtm.h>
#include <limine_requests.h>

PML4_t 				*PML4T;
Contiguous_PDPT_t 	*ALL_PDPT;
Contiguous_PD_t 	*ALL_PD;
Contiguous_PT_t 	*ALL_PT;

int MAXPHYADDR;
struct limine_kernel_address_response kernel_address_response;

/*
    Paging Structures Memory Layout for Quick Translation

    PML4 Table
    512 PDP Tables
    512 * 512 Page Directories
    512 * 512 * 512 Page Tables
*/

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
    // designate a specific address for the strucure to begin
    // start filling them pages (quad loop incoming!!)
    // map the exact same way as the entry memory layout)
    // THERE ARE CERTAIN REGIONS THAT MUST JUST BE KERNEL 1GB PAGING

    // the rest is free game

    kernel_address_response = *(kernel_address_request.response);

    // let's just map the first GB

}

void initialize_paging() {
	MAXPHYADDR = get_MAXPHYADDR();
	setup_all_paging_structures();
}
