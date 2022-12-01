#ifndef KMALLOC_H
#define KMALLOC_H

#include <stdint.h>

extern const int BSS_BEGIN;
extern const uint32_t MAXMEM;
extern uint32_t memused;
extern uint32_t memleft;

typedef struct memblock {
    struct memblock* prev;
    struct memblock* next;
    uint32_t addr_loc;
    uint32_t chunk_size;
    void* data;
} mblock_t;

typedef mblock_t* mblockptr_t;

extern mblockptr_t MEMROOT;
extern mblockptr_t last_block;

void init_mem_model();
mblockptr_t kmalloc(uint32_t req_size);
void kfree(mblockptr_t block);

#endif