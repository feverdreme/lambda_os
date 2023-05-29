#ifndef PAGING_H
#define PAGING_H
#ifdef __cplusplus
extern "C" {
#endif

#include <cpuid.h>
#include <envvars.h>
#include <limine.h>

// This can only map 4kb pages, other direct mappings are too complex right now

#ifdef IA32E_PAGING

// CR4.PCIDE = 0

#define KiB						0x400ULL
#define MiB						0x100000ULL
#define GiB						0x40000000ULL

#define PT_PAGE_SIZE			(4*KiB)
#define PD_PAGE_SIZE			(2*MiB)

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

typedef uint64_t		 	Page_Entry_t;

typedef Page_Entry_t 		Paging_Structure_t[512];

typedef Page_Entry_t		*Page_Table_t;
typedef Page_Entry_t		*Page_Directory_t;
typedef Page_Entry_t		*PDPT_t;
typedef Page_Entry_t		*PML4_t;

extern PML4_t PML4T;

/**
 * @brief Set a 4kb page table entry located at a virtual address, along with necesary heirarchical structures. If it already exists returns a pointer to the existing entry. Sets present bit. Does not cascade enable. DOES NOT OVERRIDE 1GB MAPPING
 * 
 * @param phys_addr 
 * @param vaddr 
 * @return Page_Entry_t* The page table entry with the physical address.
 */
Page_Entry_t *map_4kb_page(uint64_t phys_addr, uint64_t vaddr, uint8_t flags);

/**
 * @brief Set a 2mb page table entry located at a virtual address, along with necesary heirarchical structures. If it already exists returns a pointer to the existing entry. Sets present bit. Does not cascade enable. DOES NOT OVERRIDE 1GB MAPPING
 * 
 * @param phys_addr 
 * @param vaddr 
 * @return Page_Entry_t* The page directory entry with the physical address.
 */
Page_Entry_t *map_2mb_page(uint64_t phys_addr, uint64_t vaddr, uint8_t flags);

/**
 * @brief Sets up all the paging structures
 * 
 */
void init_PML4T();

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

#ifdef __cplusplus
}
#endif
#endif