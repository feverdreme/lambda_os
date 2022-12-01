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
} memblock_t;

extern struct memblock* MEMROOT;
extern struct memblock* last_block;

void init_mem_model();
struct memblock* kmalloc(uint32_t req_size);
void kfree(struct memblock* block);

#endif