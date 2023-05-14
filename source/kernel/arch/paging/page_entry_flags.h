#ifndef PAGE_ENTRY_FLAGS_H
#define PAGE_ENTRY_FLAGS_H

#define PE_RW	(1<<1)	// read/write
#define PE_US	(1<<2)	// user/supervisor
#define PE_PWT	(1<<3)	// page-level write-through
#define PE_PCD	(1<<4)	// page-level cache disable		

#endif