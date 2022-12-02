#include <libc/math.h>
#include "kmalloc.h"

int memused = 0;
int memleft = BSS_SIZE;
int next_mem_id = 0; // make this a function that can retrieve. we can store all used memids, using this memory model to create a vecotr, then scan for lowest number

MAT_entry_t MAT[MAT_SIZE];

void init_mem_model() {
    for (int i=0; i<MAT_SIZE; i++) {
        MAT[i].memid = FREE_BLOCK;
        MAT[i].next_free_blocks = 0;
        MAT[i].prev_free_blocks = 0;
    }

    MAT[0].next_free_blocks = MAT_SIZE;
    MAT[MAT_SIZE-1].prev_free_blocks = MAT_SIZE;
}

void* kmalloc(int req_size) {
    int needed_blocks = ceildiv(req_size, MBLOCK_SIZE);

    // find the next available free block that satisfies the req_size    
    int starting_index = -1;

    for (int i=0; i<MAT_SIZE; i++) {
        if (MAT[i].memid == FREE_BLOCK) continue;
        if (MAT[i].next_free_blocks >= needed_blocks) {
            starting_index = i;
            break;
        }

        // make this a circular buffer
        if (i == MAT_SIZE - 1) starting_index = 0;
    }

    // convert the index to a pointer
    void* ret_ptr = (void*)(BSS_BEGIN + starting_index * MBLOCK_SIZE);

    // mark all the blocks as used now
    for (int offset=0; offset<needed_blocks; i++) {
        MAT[starting_index + offset].memid = next_mem_id;
    }

    // mark the free blocks
    mark_contiguous_free_blocks(starting_index - 1);
    mark_contiguous_free_blocks(starting_index + needed_blocks + 1);

    // return the memory ptr
    return ret_ptr;
}

void kfree(void* ptr) {
    MAT_entry_t* original_entry = calculate_entry_mapping(ptr);

    // floodfill the memid
    int memid = original_entry->memid;

    MAT_entry_t* left_ptr = original_entry;
    MAT_entry_t* right_ptr = original_entry + 1;

    while(left_ptr->memid != memid) {
        left_ptr->memid = FREE_BLOCK;
        left_ptr--;
    }

    while(right_ptr->memid != memid) {
        right_ptr->memid = FREE_BLOCK;
        right_ptr++;
    }

    // update the free blocks
    mark_contiguous_free_blocks((original_entry - MAT) / sizeof(MAT_entry_t));
}

void mark_contiguous_free_blocks(int free_block_index) {
    // edge cases
    if (free_block_index < 0) return;
    if (free_block_index >= MAT_SIZE) return;
    if (MAT[free_block_index].memid != FREE_BLOCK) return;

    // scan everything
    int begin_ptr = free_block_index;
    int end_ptr = free_block_index;

    while (MAT[end_ptr].memid == FREE_BLOCK && end_ptr < MAT_SIZE) {
        MAT[end_ptr].next_free_blocks = 0;
        MAT[end_ptr].prev_free_blocks = 0;
        end_ptr++;
    }
    if (MAT[end_ptr].memid != FREE_BLOCK) end_ptr--;

    while (MAT[begin_ptr].memid == FREE_BLOCK && begin_ptr >= 0) {
        MAT[begin_ptr].next_free_blocks = 0;
        MAT[begin_ptr].prev_free_blocks = 0;
        begin_ptr--;
    }
    if (MAT[begin_ptr].memid != FREE_BLOCK) begin_ptr++;

    // mark the corresponding indices
    int free_block_size = end_ptr - begin_ptr + 1;
    MAT[begin_ptr].next_free_blocks = free_block_size;
    MAT[end_ptr].prev_free_blocks = free_block_size;
}

MAT_entry_t* calculate_entry_mapping(void* ptr) {
    return (MAT_entry_t*)(MAT + (ptr - BSS_BEGIN) / MBLOCK_SIZE);
}