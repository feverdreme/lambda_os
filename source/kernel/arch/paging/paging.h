#ifndef PAGING_H
#define PAGING_H

#include <cpuid.h>
#include <envvars.h>
#include <limine.h>

// This can only map 4kb pages, other direct mappings are too complex right now

#ifdef IA32E_PAGING

// CR4.PCIDE = 0

#define NUM_PDPT                (512)
#define NUM_PAGE_DIRECTORIES    (512*512)
#define NUM_PAGE_TABLES         (512*512*512)

#define PE_READ_WRITE	        (1<<1)	// read/write
#define PE_USER_SUPERVISOR	    (1<<2)	// user/supervisor
#define PE_PLEVEL_WRITE_THROUGH	(1<<3)	// page-level write-through
#define PE_PLEVEL_CACHE_DISABLE	(1<<4)	// page-level cache disable		

// these type constants are defined by me

#define PE_PML4E_TYPE           (1)
#define PE_PDPTE_TYPE           (1<<2)
#define PE_PDE_TYPE             (1<<3)
#define PE_PTE_TYPE             (1<<4)
#define PE_MAPS_TO_PAGE			(1<<5)  // third bit
#define PE_IS_PRESENT			(1<<6)  // fourth bit

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

extern struct limine_kernel_address_response kernel_address_response;

/**
 * @brief Detects what type of paging structure a Page_Entry_t object is.
 * 
 * @param pe A pointer to the page entry.
 * @return Consult the PE_TYPE constants.
 */
uint8_t detect_page_entry_type(Page_Entry_t *pe);

/**
 * @brief Set a 4kb page table entry located at a virtual address, along with necesary heirarchical structures. If it already exists returns a pointer to the existing entry. Does not cascade enable. DOES NOT OVERRIDE 1GB MAPPING
 * 
 * @param phys_addr 
 * @param vaddr 
 * @return Page_Entry_t* The page table entry with the physical address.
 */
Page_Entry_t *map_4kb_page(void *phys_addr, void *vaddr, uint8_t pe_flags);

/**
 * @brief Set a 2mb page table entry located at a virtual address, along with necesary heirarchical structures. If it already exists returns a pointer to the existing entry. Does not cascade enable. DOES NOT OVERRIDE 1GB MAPPING
 * 
 * @param phys_addr 
 * @param vaddr 
 * @return Page_Entry_t* The page directory entry with the physical address.
 */
Page_Entry_t *map_2mb_page(void *phys_addr, void *vaddr);

/**
 * @brief Set a 1gb page table entry located at a virtual address, along with necesary heirarchical structures. If it already exists returns a pointer to the existing entry. Does not cascade enable.
 * 
 * @param phys_addr 
 * @param vaddr 
 * @return Page_Entry_t* The page directory pointer table entry with the physical address.
 */
Page_Entry_t *map_1gb_page(void *phys_addr, void *vaddr);

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