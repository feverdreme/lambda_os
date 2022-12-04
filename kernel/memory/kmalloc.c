#include "kmalloc.h"

#include <envvars.h>
#include <libc/math.h>
#include <stdbool.h>

#include "../graphics/puts.h"

int memused = 0;
int memblocksleft = MAT_SIZE;
unsigned int next_mem_id =
    1;  // make this a function that can retrieve. we can store
        // all used memids, using this memory model to create a
        // vector, then scan for lowest number

const MAT_section_t MAT_section_NULL =
    (const MAT_section_t){.memid = -1, .begin_ind = -1, .end_ind = -1};

MAT_entry_t MAT[MAT_SIZE];

void possible_memid_sanity_check() {
#if MAT_SIZE > OS_MAXUINT - 1
    kpanic("CAN'T GARUNTEE NEXT_MEM_ID (PIGEONHOLE PRINCIPLE)");
#endif
}

void init_mem_model() {
    possible_memid_sanity_check();

    // for each block, update with values assuming all blocks are free
    for (int mb_ind = 0; mb_ind < MAT_SIZE; mb_ind++) {
        MAT[mb_ind].memid = FREE_BLOCK;
        MAT[mb_ind].prev_free_ind = 0;
        MAT[mb_ind].next_free_ind = MAT_END;
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

            // check that we don't overstep the index. if we do, then return an
            // error
            if (mb_ind >= MAT_SIZE) kpanic("MEMORY LIMIT EXCEEDED");

            // jump to the next free blocks
            mb_ind = MAT[mb_ind].next_free_ind;
        }
    }

    // sanity check that the mb_ind we found is valid
    if (valid_mb == -1 || MAT[valid_mb].memid != FREE_BLOCK ||
        valid_mb + req_blocks >= MAT_SIZE)
        kpanic("MEMORY LIMIT EXCEEDED");

    // update indices of blocks surrounding memory

    // update blocks before
    if (valid_mb - 1 >= 0) {
        /*
            Case 1: Previous blocks are already allocated
                Set all blocks in prev_alloc to update indicies for their next_free_ptr 
            Case 2?: Previous blocks are free (for some reason) 
                Set all blocks in prev_free to update indices for their next_free_ptr

            Combine these two cases: check for status of memid.
            Then floodfill all of that memid to update the next_free_ptr to be valid_mb + req_blocks
        */

        int flood_memid = MAT[valid_mb - 1].memid;
        for (int mb_ind = valid_mb - 1;
             MAT[mb_ind].memid == flood_memid && mb_ind >= 0; mb_ind--) {
            MAT[mb_ind].next_free_ind = valid_mb;
        }
    }

    // update blocks after
    if (valid_mb + 1 < MAT_SIZE) {
        // same algorithm applies just forward

        int flood_memid = MAT[valid_mb + 1].memid;
        for (int mb_ind = valid_mb + 1;
             MAT[mb_ind].memid == flood_memid && mb_ind < MAT_SIZE; mb_ind++) {
            MAT[mb_ind].prev_free_ind = valid_mb + req_blocks - 1;
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
    next_mem_id++;

    // final return value
    return (void*)(BSS_BEGIN + valid_mb * MBLOCK_SIZE);
}

void kfree(void* ptr) {
    // Flood-fill mark all the blocks of the same memid as FREE
    int block_begin = calculate_mblock_index(ptr);
    int block_end = MAT[block_begin].next_free_ind - 1;

    MAT_floodfill(block_begin, FREE_BLOCK, -2, -2);

    // Discover of there exists left and right sections

    // check for left block
    bool leftexists = false;
    bool leftisalloc;
    int left_section_begin;
    int left_section_end;

    if (block_begin >= 1) {
        leftexists = true;

        int leftmemid = MAT[block_begin - 1].memid;
        leftisalloc = leftmemid != FREE_BLOCK;

        int mb_ind = block_begin - 1;
        while (mb_ind >= 0 && MAT[mb_ind].memid == leftmemid) {
            left_section_begin = mb_ind;
            mb_ind--;
        } 

        left_section_end = block_begin - 1;
    }

    // check for right block
    bool rightexists = false;
    bool rightisalloc;
    int right_section_begin;
    int right_section_end;

    if (block_end < MAT_END) {
        rightexists = true;

        int rightmemid = MAT[block_end + 1].memid;
        rightisalloc = rightmemid != FREE_BLOCK;

        int mb_ind = block_end + 1;
        while (mb_ind < MAT_END && MAT[mb_ind].memid == rightmemid) {
            right_section_end = mb_ind;
            mb_ind++;
        } 

        right_section_begin = block_end + 1;
    }

    // calculate what the bounds are the new contiguous free blocks
    int cont_free_begin = block_begin;
    int cont_free_end = block_end;

    // update the contiguous free blocks boundary and reset the indices
    if (leftexists && !leftisalloc) {
        cont_free_begin = left_section_begin;

        if (cont_free_begin == 0) leftexists = false;
        else {
            int leftmemid = MAT[cont_free_begin - 1].memid;

            int mb_ind = cont_free_begin - 1;
            while (mb_ind >= 0 && MAT[mb_ind].memid == leftmemid) {
                left_section_begin = mb_ind;
                mb_ind--;
            } 

            left_section_end = block_begin - 1;
        }
    }

    if (rightexists && !rightisalloc) {
        cont_free_end = right_section_end;

        if (cont_free_end == MAT_END) rightexists = false;
        else {
            int rightmemid = MAT[cont_free_end + 1].memid;

            int mb_ind = cont_free_end + 1;
            while (mb_ind < MAT_END && MAT[mb_ind].memid == rightmemid) {
                right_section_end = mb_ind;
                mb_ind++;
            } 

            right_section_begin = block_end + 1;
        }
    }

    // set the incdices and memid of the contiguous free blocks
    MAT_set(
        cont_free_begin,
        cont_free_end,
        FREE_BLOCK,
        cont_free_begin,
        cont_free_end
    );

    // alter left blocks
    if (leftexists)
        MAT_set_next_free_ind(
            left_section_begin,
            left_section_end,
            cont_free_begin
        );
    
    if (rightexists) {
        MAT_set_prev_free_ind(
            right_section_begin,
            right_section_end,
            cont_free_end
        );
    }
}

int calculate_mblock_index(void* ptr) {
    return ((int)ptr - BSS_BEGIN) / MBLOCK_SIZE;
}

void MAT_set(int begin, int end, int new_memid, int new_prev_free_ind,
             int new_next_free_ind) {
    for (int mb_ind = begin; mb_ind <= end; mb_ind++) {
        MAT[mb_ind].memid = new_memid;
        MAT[mb_ind].prev_free_ind = new_prev_free_ind;
        MAT[mb_ind].next_free_ind = new_next_free_ind;
    }
}

void MAT_set_memid(int begin, int end, int new_memid) {
    for (int mb_ind = begin; mb_ind <= end; mb_ind++) {
        MAT[mb_ind].memid = new_memid;
    }
}

void MAT_set_prev_free_ind(int begin, int end, int new_prev_free_ind) {
    for (int mb_ind = begin; mb_ind <= end; mb_ind++) {
        MAT[mb_ind].prev_free_ind = new_prev_free_ind;
    }
}

void MAT_set_next_free_ind(int begin, int end, int new_next_free_ind) {
    for (int mb_ind = begin; mb_ind <= end; mb_ind++) {
        MAT[mb_ind].next_free_ind = new_next_free_ind;
    }
}

void MAT_floodfill(int flood_ind, int new_memid, int new_prev_free_ind,
                   int new_next_free_ind) {
    int flood_memid = MAT[flood_ind].memid;

    // left floodfill
    for (int left_ind = flood_ind;
         left_ind >= 0 && MAT[left_ind].memid == flood_memid; left_ind--) {
        MAT[left_ind].memid = new_memid;
        MAT[left_ind].prev_free_ind = new_prev_free_ind;
        MAT[left_ind].next_free_ind = new_next_free_ind;
    }

    // right floodfill
    for (int right_ind = flood_ind + 1;
         right_ind < MAT_SIZE && MAT[right_ind].memid == flood_memid;
         right_ind++) {
        MAT[right_ind].memid = new_memid;
        MAT[right_ind].prev_free_ind = new_prev_free_ind;
        MAT[right_ind].next_free_ind = new_next_free_ind;
    }
}

void MAT_floodfill_memid(int flood_ind, int new_memid) {
    int flood_memid = MAT[flood_ind].memid;

    // left floodfill
    for (int left_ind = flood_ind;
         left_ind >= 0 && MAT[left_ind].memid == flood_memid; left_ind--) {
        MAT[left_ind].memid = new_memid;
    }

    // right floodfill
    for (int right_ind = flood_ind + 1;
         right_ind < MAT_SIZE && MAT[right_ind].memid == flood_memid;
         right_ind++) {
        MAT[right_ind].memid = new_memid;
    }
}

void MAT_floodfill_prev_free_ind(int flood_ind, int new_prev_free_ind) {
    int flood_memid = MAT[flood_ind].memid;

    // left floodfill
    for (int left_ind = flood_ind;
         left_ind >= 0 && MAT[left_ind].memid == flood_memid; left_ind--) {
        MAT[left_ind].prev_free_ind = new_prev_free_ind;
    }

    // right floodfill
    for (int right_ind = flood_ind + 1;
         right_ind < MAT_SIZE && MAT[right_ind].memid == flood_memid;
         right_ind++) {
        MAT[right_ind].prev_free_ind = new_prev_free_ind;
    }
}

void MAT_floodfill_next_free_ind(int flood_ind, int new_next_free_ind) {
    int flood_memid = MAT[flood_ind].memid;

    // left floodfill
    for (int left_ind = flood_ind;
         left_ind >= 0 && MAT[left_ind].memid == flood_memid; left_ind--) {
        MAT[left_ind].next_free_ind = new_next_free_ind;
    }

    // right floodfill
    for (int right_ind = flood_ind + 1;
         right_ind < MAT_SIZE && MAT[right_ind].memid == flood_memid;
         right_ind++) {
        MAT[right_ind].next_free_ind = new_next_free_ind;
    }
}