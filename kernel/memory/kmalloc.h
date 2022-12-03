#ifndef KMALLOC_H
#define KMALLOC_H

#define FREE_BLOCK -1

#include <stdint.h>

// CONSTANTS
#define BSS_BEGIN 0x3E00
#define BSS_SIZE 0x10000
#define MBLOCK_SIZE 16
#define MAT_SIZE (BSS_SIZE / MBLOCK_SIZE + 1)

extern int memused;
extern int memblocksleft;
extern int next_mem_id;

// Memory Allocation Table structs

typedef struct MAT_entry {
    // id for allocating contiguous blocks of memory all under the same malloc call
    int memid;

    /*
        if free, index to the start of the contiguous free blocks
        if not free, index to the end of the previous contiguous free blocks
    */
    int prev_free_ind;

    /*
        if free, index to the end of the contiguous free blocks
        if not free, index to the start of the next contiguous free blocks
    */
    int next_free_ind;

} MAT_entry_t;

extern MAT_entry_t MAT[MAT_SIZE];

// User memory functions

void init_mem_model();
void* kmalloc(int req_size);
void kfree(void* ptr);

// Utility functions to handle MAT

/**
 * @brief Calculates what MAT_entry controls an address
 *
 * @param entry A pointer to the MAT_entry
 * @return void* A pointer to the corresponding memory block
 */
MAT_entry_t* calculate_entry_mapping(void* ptr);

/**
 * @brief Takes the contiguous free blocks from an index and marks the beginning and end
 * 
 * @param free_block_index An index of any block in the contiguous thing
 */
void mark_contiguous_free_blocks(int free_block_index);

#endif
