#ifndef PAGING_H
#define PAGING_H

#include <cpuid.h>
#include <envvars.h>

static int get_MAXPHYADDR() {
    int cpuid_code = 0x80000008; // EAX code for CPUID call

    int eax, unused;
    __get_cpuid(cpuid_code, &eax, &unused, &unused, &unused);

    return eax & (0xff); // EAX[7:0]
}

#ifdef IA32E_PAGING

// CR4.PCIDE = 0

typedef struct Page_Entry {
    int present : 1;
    int flags : 4;
    int accessed : 1;
    int ignored : 1;
    int reserved : 1;
    int avl : 4;        // up to me, ignored by MMU
    uint64_t phys : 40; // includes M-1:12 and reserved bits
    int avl2 : 11;
    int xd : 1;         // execute-disable
} __attribute__((packed)) Page_Entry_t;

typedef struct Paging_Structure {
    Page_Entry_t entries[512];
} Paging_Structure_t;

typedef Paging_Structure_t Page_Table_t;
typedef Paging_Structure_t Page_Directory_t;
typedef Paging_Structure_t PDPT_t;
typedef Paging_Structure_t PML4_t;

extern PML4_t PML4_Table;
extern int MAXPHYADDR;

void fill_page_entry(Page_Entry_t *entry, uint8_t flags, void *address);

void copy_bootboot_paging();
void initialize_paging();

#endif

#endif