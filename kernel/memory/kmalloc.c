#include <libc/math.h>
#include "../graphics/puts.h"
#include "kmalloc.h"

int memused = 0;
int memblocksleft = MAT_SIZE;
int next_mem_id = 1; // make this a function that can retrieve. we can store all used memids, using this memory model to create a vector, then scan for lowest number

MAT_entry_t MAT[MAT_SIZE];

void init_mem_model() {
    // for each block, update with values assuming all blocks are free
    for (int mb_ind = 0; mb_ind < MAT_SIZE; mb_ind++) {
        MAT[mb_ind].memid = FREE_BLOCK;
        MAT[mb_ind].prev_free_ind = 0;
        MAT[mb_ind].next_free_ind = MAT_SIZE - 1;
    }
}

void* kmalloc(int req_size) {
    int req_blocks = ceildiv(req_size, MBLOCK_SIZE);

    // sanity check for number of requested blocks
    if (req_blocks > memblocksleft) kpanic("MEMORY LIMIT EXCEEDED");

    int valid_mb = -1;

    // look for the first contiguous free blocks
    for (int mb_ind = 0; mb_ind < MAT_SIZE;) {
        // check if free
        if (MAT[mb_ind].memid != FREE_BLOCK) {
            // send to the next available free
            mb_ind = MAT[mb_ind].next_free_ind;
        } else {
            // check size requirements
            int contiguous_block_size = MAT[mb_ind].next_free_ind - mb_ind + 1;

            if (contiguous_block_size >= req_blocks) {
                valid_mb = mb_ind;
                break;
            }

            // it doesn't work. jump to the next free blocks
            // jump to the end of the free blocks then overstep into non-free
            mb_ind = MAT[mb_ind].next_free_ind + 1;
            
            // check that we don't overstep the index. if we do, then return an error
            if (mb_ind >= MAT_SIZE) kpanic("MEMORY LIMIT EXCEEDED");

            // jump to the next free blocks
            mb_ind = MAT[mb_ind].next_free_ind;
        }
    }

    // sanity check that the mb_ind we found is valid
    if (valid_mb == -1 || MAT[valid_mb].memid != FREE_BLOCK || valid_mb + req_blocks >= MAT_SIZE) kpanic("MEMORY LIMIT EXCEEDED");

    // update indices of blocks surrounding memory
    
    // update blocks before
    if (valid_mb - 1 >= 0) {
        /*
            Case 1: Previous blocks are already allocated
                Set all blocks in prev_alloc to update indicies for their next_free_ptr
            Case 2?: Previous blocks are free (for some reason)
                Set all blocks in prev_free to update indices for their next_free_ptr
            
            Combine these two cases: check for status of memid. Then floodfill all of that memid to update the next_free_ptr to be valid_mb + req_blocks
        */

        int flood_memid = MAT[valid_mb - 1].memid;
        for (int mb_ind = valid_mb - 1; MAT[mb_ind].memid == flood_memid && mb_ind >= 0; mb_ind--) {
            MAT[mb_ind].next_free_ind = valid_mb + req_blocks;
        }
    }

    // update blocks after
    if (valid_mb + 1 < MAT_SIZE) {
        // same algorithm applies just forward

        int flood_memid = MAT[valid_mb + 1].memid;
        for (int mb_ind = valid_mb + 1; MAT[mb_ind].memid == flood_memid && mb_ind < MAT_SIZE; mb_ind++) {
            MAT[mb_ind].prev_free_ind = valid_mb - 1;
        }
    }

    // set blocks to be allocated
    for (int mb_offset = 0; mb_offset < req_blocks; mb_offset++) {
        MAT[valid_mb + mb_offset].memid = next_mem_id;

        // update indices
        MAT[valid_mb + mb_offset].next_free_ind = valid_mb + req_blocks;
        MAT[valid_mb + mb_offset].prev_free_ind = valid_mb - 1;
    }

    // update memory values
    memblocksleft -= req_size;
    memused += req_size;

    // final return value
    return (void*)(BSS_BEGIN + valid_mb * MBLOCK_SIZE);
}

void kfree(void* ptr) {}

void mark_contiguous_free_blocks(int free_block_index) {}

MAT_entry_t* calculate_entry_mapping(void* ptr) {
    return (MAT_entry_t*)(MAT + ((int)ptr - BSS_BEGIN) / MBLOCK_SIZE);
}