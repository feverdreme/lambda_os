#include "kmalloc.h"

const int BSS_BEGIN = 0x3E00; // arbitrary

const uint32_t MAXMEM = 0x10000;

uint32_t memused = 0;
uint32_t memleft = MAXMEM;

struct memblock* MEMROOT; 
struct memblock* last_block;

void init_mem_model() {
    // dirty memory setup at the address
    MEMROOT = (struct memblock*)(BSS_BEGIN);
    MEMROOT->addr_loc = BSS_BEGIN;
    MEMROOT->chunk_size = 1;
    MEMROOT->prev = MEMROOT;
    MEMROOT->next = MEMROOT; // if it terminates then it points to itself

    last_block = MEMROOT;
}

struct memblock* kmalloc(uint32_t req_size) {
    if (req_size > memleft) return -1;

    // create a new block

    // set the pointer to a new block
    uint32_t newaddr = last_block->addr_loc + sizeof(struct memblock) + last_block->chunk_size + 1;
    last_block->next = (struct memblock*)newaddr;

    // set the next block's prev to be the current block
    last_block->next->prev = last_block;

    // finally update the last_block pointer
    last_block = last_block->next;

    // update the values
    last_block->addr_loc = newaddr;
    last_block->chunk_size = req_size;
    last_block->next = last_block;

    // update global memory
    memused += last_block - last_block->prev;
    memleft -= last_block - last_block->prev;

    return last_block;
}

void kfree(struct memblock* block) {
    // preserve the prev and last blocks
    struct memblock* prevblock = block->prev;
    struct memblock* nextblock = block->next;
    
    // case for if this is the last block
    if (nextblock == block) {
        prevblock->next = prevblock;

        memused -= block - prevblock;
        memleft += block - prevblock;
    } else {
        // case for when it's a middle block
        prevblock->next = nextblock;
        nextblock->prev = prevblock;

        memused -= sizeof(struct memblock) + block->chunk_size;
        memleft += sizeof(struct memblock) + block->chunk_size;
    }
}