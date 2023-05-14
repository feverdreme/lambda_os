#ifndef PAGING_H
#define PAGING_H

#include <cpuid.h>
#include <envvars.h>

// This can only map 4kb pages, other direct mappings are too complex right now

static int get_MAXPHYADDR() {
    int cpuid_code = 0x80000008; // EAX code for CPUID call

    int eax, unused;
    __get_cpuid(cpuid_code, &eax, &unused, &unused, &unused);

    return eax & (0xff); // EAX[7:0]
}

#ifdef IA32E_PAGING

// CR4.PCIDE = 0

#define NUM_PDPT                (512)
#define NUM_PAGE_DIRECTORIES    (512*512)
#define NUM_PAGE_TABLES         (512*512*512)

#define PE_READ_WRITE	        (1<<1)	// read/write
#define PE_USER_SUPERVISOR	    (1<<2)	// user/supervisor
#define PE_PLEVEL_WRITE_THROUGH	(1<<3)	// page-level write-through
#define PE_PLEVEL_CACHE_DISABLE	(1<<4)	// page-level cache disable		

typedef struct Page_Entry {
    int present : 1;
    int flags : 4;
    int accessed : 1;
    int ignored : 1;
    int reserved : 1;   // in non PML4, this indicates whether it maps a page or another paging structure
    int avl : 4;        // up to me, ignored by MMU
    uint64_t phys : 40; // includes M-1:12 and reserved bits
    int avl2 : 11;
    int xd : 1;         // execute-disable
} __attribute__((packed)) 	Page_Entry_t;

typedef Page_Entry_t 		Paging_Structure_t[512];

typedef Paging_Structure_t 	Page_Table_t;
typedef Paging_Structure_t 	Page_Directory_t;
typedef Paging_Structure_t 	PDPT_t;
typedef Paging_Structure_t 	PML4_t;

typedef PDPT_t 				Contiguous_PDPT_t[512];
typedef Page_Directory_t	Contiguous_PD_t[512][512];
typedef Page_Table_t		Contiguous_PT_t[512][512][512];

extern PML4_t 				*PML4T;
extern Contiguous_PDPT_t 	*ALL_PDPT;
extern Contiguous_PD_t 		*ALL_PD;
extern Contiguous_PT_t 		*ALL_PT;

extern int MAXPHYADDR;

/**
 * @brief Set a 4kb page table entry located at a virtual address, along with necesary heirarchical structures. If it already exists returns a pointer to the existing entry. Does not cascade enable.
 * 
 * @param phys_addr 
 * @param vaddr 
 * @return Page_Entry_t* 
 */
Page_Entry_t *set_page(void *phys_addr, void *vaddr, uint8_t pe_flags);

/**
 * @brief Sets the present bit on a page entry, cascading down hierarchical structures.
 * 
 * @param pte Page table entry
 */
Page_Entry_t *enable_page_entry(void *vaddr);

/**
 * @brief Disables the present bit on ONLY the page entry.
 * 
 * @param pte Page table entry
 */
Page_Entry_t *disable_page_entry(void *vaddr);

/**
 * @brief Locates the page entry that maps to a specific virtual address
 * 
 * @param vaddr The virtual address
 * @return Page_Entry_t* A pointer to the page entry
 */
Page_Entry_t *locate_page_entry(void *vaddr);

/**
 * @brief Sets up all the paging structures
 * 
 */
void setup_all_paging_structures();

/**
 * @brief Initializes all paging for the OS, including remapping the BOOTBOOT paging and modifying cr3.
 * 
 */
void initialize_paging();

#endif

#endif