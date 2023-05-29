#ifndef PMM_H
#define PMM_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define MAX_MEMORY_SIZE 	0x100000000   					// 4 GiB
#define PAGE_SIZE       	0x1000         					// 4 KiB
#define NUM_POSSIBLE_PAGES	(MAX_MEMORY_SIZE / PAGE_SIZE)
#define PMM_BITMAP_SIZE		(NUM_POSSIBLE_PAGES / 64)		// number of bits / 64 bit integers

extern uint64_t pmm_page_bitmap_usable[PMM_BITMAP_SIZE];    // bitmap for usable memory regions
extern uint64_t pmm_page_bitmap_used[PMM_BITMAP_SIZE];      // bitmap that the pmm uses to keep track of freed and alloced pages

/**
 * @brief Marks the 64bit address corresponding to the bitmap.
 * 
 * @param bitmap The bitmap to mutate
 * @param addr The 64bit address
 * @param use The bit to set
 */
void mark_pmm_bitmap(uint64_t *bitmap, uint64_t addr, bool use);

/**
 * @brief Determines the status of an address represented in the bitmap
 * 
 * @param bitmap Bitmap to access
 * @param addr The 64bit address
 * @return The access bit
 */
bool pmm_addr_access_bit(uint64_t *bitmap, uint64_t addr);

/**
 * @brief Allocates a 4KiB-aligned page
 * 
 * @return void* The address
 */
void *pmm_alloc_page();

/**
 * @brief Allocates a 2mb aligned page
 * 
 * @return void* 
 */
void *pmm_alloc_2mb_aligned_page();

/**
 * @brief Frees the 4KiB-aligned page at an address
 * 
 * @param addr The address.
 */
void pmm_free_page(void *addr);

void pmm_init();

#ifdef __cplusplus
}
#endif
#endif