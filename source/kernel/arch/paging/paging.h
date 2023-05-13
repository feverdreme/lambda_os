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

extern PML4_t PML4T;
extern int MAXPHYADDR;

/**
 * @brief Set a page table entry located at a virtual address, along with necesary heirarchical structures. If it already exists returns a pointer to the existing entry.
 * 
 * @param phys_addr 
 * @param vaddr 
 * @return Page_Entry_t* 
 */
Page_Entry_t *set_page(void *phys_addr, void *vaddr);

/**
 * @brief Sets the present bit on a page entry
 * 
 * @param pte Page table entry
 */
void enable_page_entry(Page_Entry_t *pte);

/**
 * @brief Disables the present bit on a page entry
 * 
 * @param pte Page table entry
 */
void disable_page_entry(Page_Entry_t *pte);

/**
 * @brief Locates the page entry that maps to a specific virtual address
 * 
 * @param vaddr The virtual address
 * @return Page_Entry_t* A pointer to the page entry
 */
Page_Entry_t *locate_page_entry(void *vaddr);

/**
 * @brief Initializes all paging for the OS, including remapping the BOOTBOOT paging and modifying cr3.
 * 
 */
void initialize_paging();

#endif

#endif