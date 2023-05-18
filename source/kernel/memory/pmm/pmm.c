#include "pmm.h"

#include <arch/debug/kpanic.h>
#include <limine_requests.h>
#include <memory/mem.h>

struct limine_memmap_response *memmap_response;

uint64_t pmm_page_bitmap_usable[PMM_BITMAP_SIZE];
uint64_t pmm_page_bitmap_used[PMM_BITMAP_SIZE];

void mark_pmm_bitmap(uint64_t *bitmap, uint64_t addr, bool use){
    if (addr >= ((uint64_t)4<<30)) return;

    // divide address by 4 KiB
    addr /= PAGE_SIZE;

    // 64 page-refs in one uint64_t
    uint64_t bitmap_index = addr / 64;
    uint64_t bitmap_bit_index = addr % 64;

    if (use)
        bitmap[bitmap_index] |= ((uint64_t)1 << bitmap_bit_index);
    else
        bitmap[bitmap_index] &= ~((uint64_t)1 << bitmap_bit_index);
}

bool pmm_addr_access_bit(uint64_t *bitmap, uint64_t addr) {
    addr /= PAGE_SIZE;

    // 64 page-refs in one uint64_t
    int bitmap_index = addr / 64;
    int bitmap_bit_index = addr % 64;

    return bitmap[bitmap_index] & (1 << bitmap_bit_index);
}

// int c = 0;

void *pmm_alloc_page() {
    uint64_t found_addr = 0;

    for (uint64_t addr = 4096; addr < MAX_MEMORY_SIZE; addr += PAGE_SIZE) {
        if (pmm_addr_access_bit(pmm_page_bitmap_usable, addr) &&  !pmm_addr_access_bit(pmm_page_bitmap_used, addr)) {
            found_addr = addr;
            break;
        }
    }

    if (found_addr == 0) {
        kpanic("NO FREE PAGE FOUND: ALL MEMORY USED");
        return NULL;
    }

    // if (c++ < 50) {
    // printd(found_addr);
    // println();}

    // we've found a free page
    mark_pmm_bitmap(pmm_page_bitmap_used, found_addr, true);
    return (void*)found_addr;
}

void pmm_free_page(void *addr) {
    mark_pmm_bitmap(pmm_page_bitmap_used, (uint64_t)addr, false);
}

void pmm_init() {
    memset(pmm_page_bitmap_used, 0, sizeof(uint64_t) * PMM_BITMAP_SIZE);
    memset(pmm_page_bitmap_usable, 0, sizeof(uint64_t) * PMM_BITMAP_SIZE);

    memmap_response = memmap_request.response;

    uint64_t entry_count = memmap_response->entry_count;
    struct limine_memmap_entry **entries = memmap_response->entries;

    // iterate for usable entries
    for (uint64_t i=0; i<entry_count; i++) {
        struct limine_memmap_entry entry = *(entries[i]);

        // iterate through all pages marked
        for (uint64_t base_offset=0; base_offset < entry.length; base_offset += PAGE_SIZE)
            mark_pmm_bitmap(pmm_page_bitmap_usable, entry.base + base_offset, entry.type == LIMINE_MEMMAP_USABLE);
    }
}