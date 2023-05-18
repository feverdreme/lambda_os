#include "virtm.h"

#include <arch/debug/kpanic.h>
#include <memory/paging/paging.h>

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

void *align_address(void *addr, int bits) {
    return ((uint64_t)addr >> bits) << bits;
}