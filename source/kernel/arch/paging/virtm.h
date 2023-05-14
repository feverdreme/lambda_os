#ifndef VIRTM_H
#define VIRTM_H

#include <stdint.h>
#include <arch/paging/paging.h>

typedef struct translated_vaddr {
    uint8_t PML4i;
    uint8_t PDPTi;
    uint8_t PDi;
    uint8_t PTi;
    uint16_t PHYS;
} translated_vaddr_t;

typedef struct translated_vaddr_ptrs {
    Page_Entry_t *PML4Te;
    Page_Entry_t *PDPTe;
    Page_Entry_t *PDe;
    Page_Entry_t *PTe;
} translated_vaddr_ptrs_t;

/**
 * @brief Parses a virtual address into its paging structure indices.
 * 
 * @param vaddr 64bit virtual address
 * @return A translated indices object
 */
translated_vaddr_t get_vaddr_indices(void *vaddr);

/**
 * @brief Parses a virtual address and gets the corresponding page structure entries, regardless of whether hierarchical structures point to each other.
 * 
 * @param vaddr 64bit virtual address
 * @return A translated_vaddr_ptrs object 
 */
translated_vaddr_ptrs_t get_vaddr_paging_ptrs(void *vaddr);

#endif