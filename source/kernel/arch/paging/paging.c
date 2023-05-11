#include "paging.h"

#include "page_entry_flags.h"

PML4_t PML4_Table;
int MAXPHYADDR;

void fill_page_entry(Page_Entry_t *entry, uint8_t flags, void *address) {
    entry->present = 1;
    entry->flags = flags & 0xf; // force 4 bit flags
    entry->reserved = 0;

    // isolate first M-12 bits (M-1:12)
    entry->phys = (uint64_t)address & ((1<<(MAXPHYADDR - 12 + 1)) - 1);
}

void copy_bootboot_paging() {
    // identity map first 16G

}

void initialize_paging() {
    MAXPHYADDR = get_MAXPHYADDR();
    copy_bootboot_paging();
}
