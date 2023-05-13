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
    int PHYS_offset = (uint64_t)vaddr & 0xfff,
        PT_index = ((uint64_t)vaddr >> 12) & 0x1ff,  // 9 bit mask
        PD_index = ((uint64_t)vaddr >> 21) & 0x1ff,
        PDPT_index = ((uint64_t)vaddr >> 30) & 0x1ff,
        PML4_index = ((uint64_t)vaddr >> 39) & 0x1ff;

    translated_vaddr_t ret = {PML4_index, PDPT_index, PD_index, PT_index,
                              PHYS_offset};
    
    return ret;
}