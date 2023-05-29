#include "ioapic.h"

#include <arch/acpi/madt.h>
#include <graphics/puts.h>

void *IOAPIC_ADDRESS;

uint32_t ioapic_read(uint32_t reg) {
    volatile uint32_t *ioapic = (volatile uint32_t*)IOAPIC_ADDRESS;

    ioapic[IOAPIC_IOREGSEL] = reg & 0xff;
    
    return ioapic[IOAPIC_IOWIN];
}

void ioapic_write(uint32_t reg, uint32_t data) {
    volatile uint32_t *ioapic = (volatile uint32_t*)IOAPIC_ADDRESS;

    ioapic[IOAPIC_IOREGSEL] = reg & 0xff;
    ioapic[IOAPIC_IOWIN] = data;
}

uint64_t ioapic_read_entry(int index) {
    return ioapic_read(redirect_tbl_index(index)) + 
    ((uint64_t)ioapic_read(redirect_tbl_index(index) + 1) << 32);
}

void ioapic_write_entry(int index, uint8_t vector, uint32_t flags, uint32_t dest) {
    ioapic_write(redirect_tbl_index(index), vector | flags);
    ioapic_write(redirect_tbl_index(index) + 1, (dest & 0xff) << 24);
}

void ioapic_init() {
    parse_madt();
}