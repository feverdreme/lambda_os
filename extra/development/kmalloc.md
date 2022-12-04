# Memory Manager Algorithm Explanations

## `kmalloc`

1. Calculate the number of blocks needed for the requested size
2. Sanity check: number of requested blocks doesn't exceed `memblocksleft`
3. Search for a valid memory block index that is big enough. Loop through from `0` to `MAT_SIZE` with no increment
    1. If the block isn't free, use `next_free_ind` to get to next free block
    2. If the block is free
        1. Calculate `contiguous_block_size` to check if it satisfies the size requirement
        2. If it does, set `valid_md` and **break** the loop
        3. Jump `mb_ind` to `next_free_ind`, which should be the end of the contiguous free blocks. Then add 1 to enter an allocated space in order to jump ahead once more
        4. Perform an out-of-bounds check. `kpanic` if you are, since that means there are no adequate free sections
        5. Jump to the next free block using `next_free_ind`
4. Sanity check: `valid_mb != -1`, the default, the index is a `FREE_BLOCK`, and the found section doesn't exceeed size for some reason.
*NOTE: at this point, `mb_ind` is garunteed to be at the leftmost index of the free section*
5. Flood-fill left and right adjacent sections (if they exist) and update their indices
6. Set the free-section blocks to be allocated and update corresponding indices. *NOTE: these updated indices might go out of bounds. They will be corrected and updated once the next `kfree` is called to make these indices valid*
7. Update memory values
8. Return the pointer according to `valid_mb`

## `kfree`

1. Calculate the index of the MAT given the pointer using `calculate_block_index()`
2. Floodfill the blocks and mark them all as free
3. Find the bounds of the left and right adjacent sections using their left and right indicies (remember it's different depending if theyre free or not)

There are many cases once we have discovered the left and right adjacent sections

* Case 1: Left and right exist
  * Subcase 1.1: Both free
    1. Mark all three as if it were one contiguous block
    2. Check for adjacent allocated. If they exist, then flood-update
  * Subcase 1.2: Left free right allocated
    1. For both free:
        1. Mark `prev_free_ind` according to left block
        2. Mark `next_free_ind` making freed block as the end
    2. For right allocated:
        1. Mark prev_free_ind according to block
    3. If left-left-alloc exists, then flood-update
  * Subcase 1.3: Left allocated right free
    1. Subcase 1.2 flipped
  * Subcase 1.4: Both allocated
    1. For free block: The block is insulated. Mark according to itself
    2. For both allocated: Mark next and prev ind respectively
* Case 2: Left exists right doesn't
  * Subcase 2.1: Left free
    1. Mark both free blocks accordingly
    2. If left-left-alloc exists, mark accordingly
  * Subcase 2.2 Left allocated
    1. Mark freed block
    2. Mark left allocated right `next_free_ind`
* Case 3: Right exists left doesn't
  * Case 2 but flipped
* Case 4: Neither exist??
  * This only happens if you initially allocated the entire allowed size... I shouldn't let this happen but currently it's allowed
  * Literally just call `init_mem_model` at this point it will do the same thing

Remember for all of these to check for out-of-bounds errors
