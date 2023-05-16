#include "paging.h"

#include <stdbool.h>
#include <arch/paging/virtm.h>
#include <limine_requests.h>
#include <arch/cpuid_query.h>

Full_Paging_Structure_t *FULL_PAGING_STRUCTURE;

int MAXPHYADDR;

struct limine_kernel_address_response kernel_address_response;
struct limine_hhdm_response hhdm_response;

// FIXME: DOESNT WORK NAME COLLISIONS
// uint8_t detect_page_entry_type(Page_Entry_t *pe) {
//     // detect what type
//     int pe_type;

//     // THIS ASSUME THIS IS SIGNED
//     // MAKE SURE THIS CONVERSION WORKS?? THE TYPE IS GONNA BE WEIRD
//     if ((int64_t)pe >= (int64_t)ALL_PT) 
//         pe_type = PE_PTE_TYPE;
//     else if ((int64_t)pe >= (int64_t)ALL_PD)
//         pe_type = PE_PDE_TYPE;
//     else if ((int64_t)pe >= (int64_t)ALL_PDPT)
//         pe_type = PE_PDPTE_TYPE;
//     else
//         pe_type = PE_PML4E_TYPE;
    
//     bool is_present = pe->present;
//     bool maps_to_page = pe->reserved;

//     return pe_type + (maps_to_page<<5) + (is_present<<6);
// }

Page_Entry_t *map_4kb_page(void *phys_addr, void *vaddr, uint8_t pe_flags) {
    // TODO: check to make sure 1GB mapping doesn't exist in PDPTe

    Page_Entry_t *pte = locate_page_entry(vaddr);

	pte->phys = (uint64_t)(phys_addr);
	pte->flags = pe_flags;
    pte->present = 1;

	return pte;
}

Page_Entry_t *map_2mb_page(void *phys_addr, void *vaddr) {
    translated_vaddr_ptrs_t ptrs = get_vaddr_paging_ptrs(vaddr);

    Page_Entry_t *pde = ptrs.PDe;

    pde->phys = (uint64_t)(phys_addr) << PD_ADDRESS_BITSHIFT;
    pde->present = 1;
    pde->reserved = 1;

    
    return pde;
}

Page_Entry_t *map_1gb_page(void *phys_addr, void *vaddr) {
    translated_vaddr_ptrs_t ptrs = get_vaddr_paging_ptrs(vaddr);

    Page_Entry_t *pdpte = ptrs.PDPTe;

    pdpte->phys = (uint64_t)(phys_addr) << PDPT_ADDRESS_BITSHIFT;
    pdpte->present = 1;
    pdpte->reserved = 1;

    return pdpte;
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
    // TODO: add checks that this page entry is actually enabled. there might not be a direct mapping to this because a higher structure doesnt point to this
    translated_vaddr_t idcs = get_vaddr_indices(vaddr);

    return &(FULL_PAGING_STRUCTURE->ALL_PT)[idcs.PML4i][idcs.PDPTi][idcs.PDi][idcs.PTi];
}

void setup_all_paging_structures() {
    FULL_PAGING_STRUCTURE = (Full_Paging_Structure_t*)PAGING_PHYS_ADDRESS;

    // set all PML4Te to not present and correct physical address
    for (int PML4Ti=0; PML4Ti<512; PML4Ti++) {
        Page_Entry_t *pe = &FULL_PAGING_STRUCTURE->PML4T[PML4Ti];

        pe->present = 0;
        pe->phys = (uint64_t)(PAGING_PHYS_ADDRESS) + sizeof(PML4_t) + PML4Ti * sizeof(PDPT_t);
    }

    // get the PML4i for the hhdm and kernel virtual addresses and set to present
    // i'm not using get_vaddr_indices for this
    uint64_t hhdm_pml4i = ((*(hhdm_request.response)).offset >> 39) & 0x1ff;
    uint64_t kernel_pml4i = ((*(kernel_address_request.response)).virtual_base >> 39) & 0x1ff;

    FULL_PAGING_STRUCTURE->PML4T[hhdm_pml4i].present = 1;
    FULL_PAGING_STRUCTURE->PML4T[kernel_pml4i].present = 1;
}

void setup_default_mapping() {
    kernel_address_response = *(kernel_address_request.response);

    hhdm_response = *(hhdm_request.response);
    uint64_t hhdm_offset = hhdm_response.offset;

    // printd(kernel_address_response.physical_base);
    // printd(hhdm_offset);

    // Map all physical memory
    for (uint64_t offset = 0; offset < 4 * PDPT_PAGE_SIZE; offset += PDPT_PAGE_SIZE) {
        map_1gb_page((void *)offset, (void*)(hhdm_offset + offset));
    }

    // Map the kernel
    map_1gb_page((void *)kernel_address_response.physical_base, (void *)kernel_address_response.virtual_base);
}

void initialize_paging() {
	MAXPHYADDR = get_MAXPHYADDR();
	setup_all_paging_structures();
}
