#ifndef PAGE_ENTRY_FLAGS_H
#define PAGE_ENTRY_FLAGS_H

#define PE_READ_WRITE	        (1<<1)	// read/write
#define PE_USER_SUPERVISOR	    (1<<2)	// user/supervisor
#define PE_PLEVEL_WRITE_THROUGH	(1<<3)	// page-level write-through
#define PE_PLEVEL_CACHE_DISABLE	(1<<4)	// page-level cache disable		

#endif