#include "virtm.h"

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
    9 bits taken for PT index PT

    12 bit physical offset
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
        &(*PML4T)[idcs.PML4i],
        &(*ALL_PDPT)[idcs.PML4i][idcs.PDPTi],
        &(*ALL_PD)[idcs.PML4i][idcs.PDPTi][idcs.PDi],
        &(*ALL_PT)[idcs.PML4i][idcs.PDPTi][idcs.PDi][idcs.PTi]
    };

    return ret;
}