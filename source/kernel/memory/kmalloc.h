#ifndef KMALLOC_H
#define KMALLOC_H

#include <stdint.h>
#include <stdbool.h>

#include <envvars.h>

/* -------------------------------------------------------------------------- */
/*                                  CONSTANTS                                */
/* -------------------------------------------------------------------------- */

#define FREE_BLOCK 0

#define BSS_SIZE 0x10000
#define BSS_BEGIN ((uint32_t)(&mmio) - BSS_SIZE)
#define MBLOCK_SIZE 16
#define MAT_SIZE (BSS_SIZE / MBLOCK_SIZE + 1)
#define MAT_END (MAT_SIZE - 1)

/* -------------------------------------------------------------------------- */
/*                       Memory Allocation Table structs                      */
/* -------------------------------------------------------------------------- */

typedef struct MAT_entry {
    // id for allocating contiguous blocks of memory all under the same malloc call
    int memid;

    /*
        If free, index to the start of the contiguous free blocks
        If not free, index to the end of the previous contiguous free blocks
    */
    int prev_free_ind;

    /*
        If free, index to the end of the contiguous free blocks
        If not free, index to the start of the next contiguous free blocks
    */
    int next_free_ind;

} MAT_entry_t;

/**
 * @brief Descriptor for contiguous sections of memory blocks.
 * ! Meant only to be used as a return type
 */
typedef struct MAT_section {
    int memid;
    int begin_ind;
    int end_ind;
} MAT_section_t;

extern const MAT_section_t MAT_section_NULL;

/* ----------------------------- MAT declaration ---------------------------- */

extern MAT_entry_t MAT[MAT_SIZE];

extern int memused;
extern int memblocksleft;
extern unsigned int next_mem_id;

/* -------------------------------------------------------------------------- */
/*                            User memory functions                           */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initializes MAT as all free
 * 
 */
void init_mem_model();

/**
 * @brief Allocates memory in MAT (no restrictions)
 * 
 * @param req_size Requested memory size in bytes
 * @return void* A pointer to the allocated memory section
 */
void* kmalloc(int req_size);

/**
 * @brief Frees memory section that the memory pointer belongs to
 * 
 * @param ptr ptr to the FRONT of the memory section
 */
void kfree(void* ptr);

/* -------------------------------------------------------------------------- */
/*                       Utility functions to handle MAT                      */
/* -------------------------------------------------------------------------- */

/**
 * @brief Calculates the index of the MAT_entry that controls the address
 *
 * @param entry A pointer to the MAT_entry
 * @return void* A pointer to the corresponding memory block
 */
int calculate_mblock_index(void* ptr);

/**
 * @brief Sets MAT_entries give specified bounds (inclusive)
 * 
 * @param begin Begin index
 * @param end End index (inclusive)
 * @param new_memid memid to set
 * @param new_prev_free_ind prev_free_ind to set
 * @param new_next_free_ind next_free_ind to set
 */
void MAT_set(int begin, int end, int new_memid, int new_prev_free_ind, int new_next_free_ind);

void MAT_set_memid(int begin, int end, int new_memid);

void MAT_set_prev_free_ind(int begin, int end, int new_prev_free_ind);

void MAT_set_next_free_ind(int begin, int end, int new_next_free_ind);

/**
 * @brief Sets MAT_entries through floodfill by memid
 * 
 * @param flood_ind Index of MAT section
 * @param new_memid memid to set
 * @param new_prev_free_ind prev_free_ind to set
 * @param new_next_free_ind next_free_ind to set
 */
void MAT_floodfill(int flood_ind, int new_memid, int new_prev_free_ind, int new_next_free_ind);

void MAT_floodfill_memid(int flood_ind, int new_memid);

void MAT_floodfill_prev_free_ind(int flood_ind, int new_prev_free_ind);

void MAT_floodfill_next_free_ind(int flood_ind, int new_next_free_ind);

/**
 * @brief Sanity check to make sure available memory size doesn't exceed possible mem_ids
 * 
 */
void possible_memid_sanity_check();

#endif
