#include "virtm.h"

#include <arch/debug/kpanic.h>
#include <arch/paging/paging.h>

/*
    64 bit address
    First 16 bits must be FFFF (canonical)

    48 bit address
    9 bits taken for PML4 index PML4E->PDPT

    39 bit address
    9 bits taken for PDPT index PDPT->PD

    30 bit address
    9 bits taken for PD index PD->PT

    21 bit address
    9 bits taken for PT index PTe

    12 bit physical offset

    PHYS[0:11]
    PT[12:20] (index for the page table)
    PD[21:29] (index for the page directory)
    PDPT[30:38] (index for the PDPT)
    PML4[39:47] (index for the PML4)
*/

translated_vaddr_t get_vaddr_indices(void *vaddr) {
    int PHYS = (uint64_t)vaddr & 0xfff,
        PTi = ((uint64_t)vaddr >> 12) & 0x1ff,  // 9 bit mask
        PDi = ((uint64_t)vaddr >> 21) & 0x1ff,
        PDPTi = ((uint64_t)vaddr >> 30) & 0x1ff,
        PML4i = ((uint64_t)vaddr >> 39) & 0x1ff;

    translated_vaddr_t ret = {PML4i, PDPTi, PDi, PTi,
                              PHYS};
    
    return ret;
}

translated_vaddr_ptrs_t get_vaddr_paging_ptrs(void *vaddr) {
    translated_vaddr_t idcs = get_vaddr_indices(vaddr);

    translated_vaddr_ptrs_t ret = {
        &(FULL_PAGING_STRUCTURE->PML4T)[idcs.PML4i],
        &(FULL_PAGING_STRUCTURE->ALL_PDPT)[idcs.PML4i][idcs.PDPTi],
        &(FULL_PAGING_STRUCTURE->ALL_PD)[idcs.PML4i][idcs.PDPTi][idcs.PDi],
        &(FULL_PAGING_STRUCTURE->ALL_PT)[idcs.PML4i][idcs.PDPTi][idcs.PDi][idcs.PTi]
    };

    return ret;
}

void *get_vaddr_from_pte(Page_Entry_t *pte) {
    // This can all be calculated from its offset in the ALL_PT space
    // 512 PDPTs * 512 PDs * 512 PTs * 512 PTes

    // TODO: implicit casting in pointer arithmetic is dangerous
    uint64_t offset = (uint64_t)pte - (uint64_t)(&FULL_PAGING_STRUCTURE->ALL_PT);

    if (offset >> 36) // if the offset > 512^4
        kpanic("INVALID PTE->VADDR DECODE:\n\tINDEX OUT OF BOUNDS");
    
    uint16_t PHYS = pte->phys;
    uint64_t PTi = offset % 512;
    uint64_t PDi = offset / 512;
    uint64_t PDPTi = offset / (512 * 512);
    uint64_t PML4i = offset / (512 * 512 * 512);

    // offset = base + 512^3 entries for PML4index(PDPT) + 512^2 entries for PDPTindex(PD) + 512 entries for PDindex (PT) + ACTUAL PT index

    // build the virtual address
    void *vaddr = 
        (void *)(PHYS + (PTi << 12) + (PDi << 21) + (PDPTi << 30) + (PML4i << 39) + ((uint64_t)(0xFFFF) << 48));

    return vaddr;
}