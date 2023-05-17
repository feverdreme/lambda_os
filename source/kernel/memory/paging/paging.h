#ifndef PAGING_H
#define PAGING_H

#include <cpuid.h>
#include <envvars.h>
#include <limine.h>

// This can only map 4kb pages, other direct mappings are too complex right now

#ifdef IA32E_PAGING

// CR4.PCIDE = 0

#define PT_PAGE_SIZE			(uint64_t)(4<<10)	// 4 kib
#define PD_PAGE_SIZE			(uint64_t)(2<<20)	// 2 mib
#define PDPT_PAGE_SIZE			(uint64_t)(1<<30)	// 1 gib

#define NUM_PDPT                (512)
#define NUM_PAGE_DIRECTORIES    (512*512)
#define NUM_PAGE_TABLES         (512*512*512)

#define PE_PRESENT				(1<<0)	// present bit
#define PE_READ_WRITE	        (1<<1)	// read/write
#define PE_USER_SUPERVISOR	    (1<<2)	// user/supervisor
#define PE_PLEVEL_WRITE_THROUGH	(1<<3)	// page-level write-through
#define PE_PLEVEL_CACHE_DISABLE	(1<<4)	// page-level cache disable
#define PE_SIZE					(1<<7)	// reserved for PML4, 1 if maps to page, 0 if not
#define PE_XD					(1<<63)	// execution disable

#define PDPT_ADDRESS_BITSHIFT	18
#define PD_ADDRESS_BITSHIFT		9	

#define PAT_UC                  0x0     // uncacheable
#define PAT_WC                  0x1     // write combining
#define PAT_WT                  0x4     // write through
#define PAT_WP                  0x5     // write protected
#define PAT_WB                  0x6		// write back
#define PAT_UNCACHED			0x7

// TODO: SHOULD BE A LINKER VARIABLE
#define PAGING_PHYS_ADDRESS		(0x20000)

typedef struct Page_Entry {
	uint64_t phys : 51;
	int reserved : 1;
    int avl2 : 11;
    int xd : 1;         // execute-disable
} __attribute__((packed)) 	Page_Entry_t;

typedef Page_Entry_t 		Paging_Structure_t[512];

typedef Paging_Structure_t 	Page_Table_t;
typedef Paging_Structure_t 	Page_Directory_t;
typedef Paging_Structure_t 	PDPT_t;
typedef Paging_Structure_t 	PML4_t;

extern PMLT4_t *PML4T;

/**
 * @brief Detects what type of paging structure a Page_Entry_t object is.
 * 
 * @param pe A pointer to the page entry.
 * @return Consult the PE_TYPE constants.
 */
uint8_t detect_page_entry_type(Page_Entry_t *pe);

/**
 * @brief Set a 4kb page table entry located at a virtual address, along with necesary heirarchical structures. If it already exists returns a pointer to the existing entry. Sets present bit. Does not cascade enable. DOES NOT OVERRIDE 1GB MAPPING
 * 
 * @param phys_addr 
 * @param vaddr 
 * @return Page_Entry_t* The page table entry with the physical address.
 */
Page_Entry_t *map_4kb_page(void *phys_addr, void *vaddr, uint8_t pe_flags);

/**
 * @brief Set a 2mb page table entry located at a virtual address, along with necesary heirarchical structures. If it already exists returns a pointer to the existing entry. Sets present bit. Does not cascade enable. DOES NOT OVERRIDE 1GB MAPPING
 * 
 * @param phys_addr 
 * @param vaddr 
 * @return Page_Entry_t* The page directory entry with the physical address.
 */
Page_Entry_t *map_2mb_page(void *phys_addr, void *vaddr, uint8_t flags);

/**
 * @brief Set a 1gb page table entry located at a virtual address, along with necesary heirarchical structures. If it already exists returns a pointer to the existing entry. Sets present bit. Does not cascade enable.
 * 
 * @param phys_addr 
 * @param vaddr 
 * @return Page_Entry_t* The page directory pointer table entry with the physical address.
 */
Page_Entry_t *map_1gb_page(void *phys_addr, void *vaddr, uint8_t flags);

/**
 * @brief Sets up all the paging structures
 * 
 */
void setup_all_paging_structures();

/**
 * @brief Sets up the mapping supported by Limine.
 * 
 */
void setup_default_mapping();

/**
 * @brief Initializes all paging for the OS, including remapping the BOOTBOOT paging and modifying cr3.
 * 
 */
void initialize_paging();

#endif

#endif