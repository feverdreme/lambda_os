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
2. Find the bounds of the block
3. Flood-find the left-adjacent and right-adjacent blocks if they exist
4. Taking into account the status of the adject blocks, demarcate bounds of new contiguous free block
5. Flood-find the left-adjacent and right-adjacent blocks of the new contiguous free block if they exist
6. Update indicies of the adjacent blocks
