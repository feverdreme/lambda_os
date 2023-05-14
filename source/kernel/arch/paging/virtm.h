#ifndef VIRTM_H
#define VIRTM_H

#include <stdint.h>

typedef struct translated_vaddr {
    uint8_t PML4_index;
    uint8_t PDPT_index;
    uint8_t PD_index;
    uint8_t PT_index;
    uint16_t PHYS_offset;
} translated_vaddr_t;

translated_vaddr_t get_vaddr_indices(void *vaddr);

#endif