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
    //TODO: Just make look_for_MAT_section inline and ignore this extra baggage
    MAT_section_t left_section = lookfor_MAT_section(block_begin, true);
    bool leftexists = !MAT_section_same(&left_section, &MAT_section_NULL);
    bool leftisalloc = left_section.memid != FREE_BLOCK;
    int left_section_begin = left_section.begin_ind;
    int left_section_end = left_section.end_ind;

    // check for right block
    MAT_section_t right_section = lookfor_MAT_section(block_end, false);
    bool rightexists = !MAT_section_same(&right_section, &MAT_section_NULL);
    bool rightisalloc = right_section.memid != FREE_BLOCK;
    int right_section_begin = right_section.begin_ind;
    int right_section_end = right_section.end_ind;

    // printd(left_section_begin, &spleen_font);
    // printc(' ', &spleen_font);
    // printd(left_section_end, &spleen_font);
    // printc(' ', &spleen_font);
    // printd(right_section_begin, &spleen_font);
    // printc(' ', &spleen_font);
    // printd(right_section_end, &spleen_font);

    // return;

    // ALL THE SUBCASES
    //TODO: Optimize the code so that it marks contiguous blocks and handles edge-cases like left-left with separate if-statements

    // Case 1: Left and right exist
    if (leftexists && rightexists) {
        // Subcase 1.1: Both free
        if (!leftisalloc && !rightisalloc) {
            MAT_set(left_section_begin, right_section_end, FREE_BLOCK,
                    left_section_begin, right_section_end);

            // check for left-left block
            if (left_section_begin >= 1)
                MAT_floodfill_next_free_ind(
                    left_section_begin - 1,
                    left_section_begin
                );
            
            // check for right-right block
            if (right_section_begin < MAT_END)
                MAT_floodfill_prev_free_ind(
                    right_section_begin + 1,
                    right_section_end
                );
        } 
        // Subcase 1.2 Left free right allocated
        else if (!leftisalloc && rightisalloc) {
            MAT_set(left_section_begin, block_end, FREE_BLOCK,
                    left_section_begin, block_end);
            
            // handle the right allocated block
            MAT_set_prev_free_ind(
                right_section_begin,
                right_section_end,
                block_end
            );
        }
        // Subcase 1.3 Left allocated right free
        else if (leftisalloc && !rightisalloc) {
            MAT_set(block_begin, right_section_end, FREE_BLOCK,
            block_begin, right_section_end);

            // handle left-allocated block
            MAT_set_next_free_ind(
                left_section_begin,
                left_section_end,
                block_begin
            );
        }
        // Subcase 1.4 Both allocated
        else {
            MAT_set(block_begin, block_end, FREE_BLOCK,
            block_begin, block_end);

            // handle left allocated block
            MAT_set_next_free_ind(
                left_section_begin,
                left_section_end,
                block_begin
            );
            // handle right allocated block
            MAT_set_prev_free_ind(
                right_section_begin,
                right_section_end,
                block_end
            );
        }
    }
    // Case 2: Left exists right doesn't
    else if (leftexists) {
        // Subcase 2.1: Left free
        if (!leftisalloc) {
            MAT_set(left_section_begin, block_end, FREE_BLOCK,
            left_section_begin, block_end);

            // check for left-left allocated
            if (left_section_begin >= 1)
                MAT_floodfill_next_free_ind(
                    left_section_begin - 1,
                    left_section_begin
                );
        }
        // Subcase 2.2 Left allocated
        else {
            MAT_set(block_begin, block_end, FREE_BLOCK,
            block_begin, block_end);

            MAT_set_next_free_ind(
                left_section_begin,
                left_section_end,
                block_begin
            );
        }
    }
    // Case 3: Right exists left doesn't
    else if (rightexists) {
        // Subcase 3.1: Right free
        if (!rightisalloc) {
            MAT_set(block_begin, right_section_end, FREE_BLOCK,
            block_begin, right_section_end);

            // check for right-right allocated
            if (right_section_end < MAT_END) {
                MAT_floodfill_prev_free_ind(
                    right_section_end + 1,
                    right_section_end
                );
            }
        }
        // Subcase 3.2: Right allocated
        else {
            MAT_set(block_begin, block_end, FREE_BLOCK,
            block_begin, block_end);

            MAT_set_prev_free_ind(
                right_section_begin,
                right_section_end,
                block_end
            );
        }
    }
    // Case 4: Neither exists
    else {
        init_mem_model();
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

//! DEPRECATED
MAT_section_t lookfor_MAT_section(int center_ind, bool left) {
    MAT_entry_t center = MAT[center_ind];
    int found_ind = -1;

    int section_begin;
    int section_end;

    if (left) {
        // keep looking left until you find a different memid
        for (int mb_ind = center_ind - 1; mb_ind >= 0; mb_ind--) {
            if (MAT[mb_ind].memid != center.memid) {
                found_ind = mb_ind;
                break;
            }
        }

        // if not found, return no found section
        if (found_ind == -1) return MAT_section_NULL;

        section_begin = MAT[found_ind].prev_free_ind;
        if (MAT[section_begin].memid != FREE_BLOCK) section_begin++;

        section_end = found_ind;
    } else {
        // keep looking right until you find a different memid
        for (int mb_ind = center_ind + 1; mb_ind < MAT_SIZE; mb_ind++) {
            if (MAT[mb_ind].memid != center.memid) {
                found_ind = mb_ind;
                break;
            }
        }

        // if not found, return no found section
        if (found_ind == -1) return MAT_section_NULL;

        section_begin = found_ind;

        section_end = MAT[section_begin].next_free_ind;
        if (MAT[section_end].memid != FREE_BLOCK) section_end--;
    }

    return (MAT_section_t){.memid = center.memid,
                           .begin_ind = section_begin,
                           .end_ind = section_end};
}

//! DEPRECATED
bool MAT_section_same(MAT_section_t *a, MAT_section_t *b) {
    return (
        a->memid == b->memid &&
        a->begin_ind == b->begin_ind &&
        a->end_ind == b->end_ind
    );
}