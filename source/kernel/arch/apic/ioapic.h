#ifndef IOAPIC_H
#define IOAPIC_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define IOAPIC_IOREGSEL 0
#define IOAPIC_IOWIN    4

#define IOREDTBL_FIXED		(0<<8)
#define IOREDTBL_LOWEST		(1<<8)
#define IOREDTBL_SMI		(2<<8)
#define IOREDTBL_NMI		(4<<8)
#define IOREDTBL_INIT		(5<<8)
#define IOREDTBL_ExtINIT	(7<<8)
#define IOREDTBL_LOGICAL	(1<<11)
#define IOREDTBL_ACTIVE_LOW	(1<<13)
#define IOREDTBL_LEVEL		(1<<15)
#define IOREDTBL_MASKED		(1<<16)

extern void *IOAPIC_ADDRESS;

/**
 * @brief Reads from the IOAPIC at the specified register.
 * 
 * @param reg The register.
 * @return uint32_t The data.
 */
uint32_t ioapic_read(uint32_t reg);

/**
 * @brief Writes to an IOAPIC register.
 * 
 * @param reg 
 * @param data 
 */
void ioapic_write(uint32_t reg, uint32_t data);

static inline int redirect_tbl_index(int index) {
	return 0x10 + index * 2;
}

/**
 * @brief Reads an entry in the IOREDTBL.
 * 
 * @param index 
 */
uint64_t ioapic_read_entry(int index);

/**
 * @brief Sets an IOREDTBL Entry
 * 
 * @param index The index in the table
 * @param entry1 The first 32 bit entry, including vector and flags
 * @param dest Destination LAPICID
 */
void ioapic_write_entry(int index, uint8_t vector, uint32_t flags, uint32_t dest);

/**
 * @brief Does IOAPIC config init processes.
 * 
 */
void ioapic_init();

#ifdef __cplusplus
}
#endif
#endif