#ifndef VIRTM_H
#define VIRTM_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <memory/paging/paging.h>

#define ALIGNED_4KB	& 0xfffffffffffff000
#define ALIGNED_2MB & 0xffffffffffe00000
#define ALIGNED_1GB & 0xffffffffc0000000

typedef struct translated_vaddr {
    uint16_t PML4i;
    uint16_t PDPTi;
    uint16_t PDi;
    uint16_t PTi;
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
translated_vaddr_t get_vaddr_indices(uint64_t vaddr);

/**
 * @brief Returns an aligned version of the address by cutting off the bits least significant bits
 * 
 * @param addr The address
 * @param bits Number of least significant bits to mask
 * @return void* The aligned address.
 */
void *align_address(void *addr, int bits);

#ifdef __cplusplus
}
#endif
#endif