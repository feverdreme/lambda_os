#include "apic.h"

#include <arch/msr.h>
#include <graphics/puts.h>

uint64_t APIC_PHYSICAL_ADDRESS;

uint64_t get_apic_base() {
    MSR_Response_t apic_base_msr = cpu_read_msr(IA32_APIC_BASE_MSR);

	uint64_t apic_addr = (apic_base_msr.low & 0xfffff000) | ((uint64_t)apic_base_msr.high << 32);

	APIC_PHYSICAL_ADDRESS = apic_addr;

    prints("APIC PHYSICAL ADDRESS: ");
    printh(APIC_PHYSICAL_ADDRESS);
    println();

	return apic_addr;
}

void enable_apic_base() {
	MSR_Response_t apic_base_msr = cpu_read_msr(IA32_APIC_BASE_MSR);

	uint32_t low = apic_base_msr.low & 0xfffff000;
	uint32_t high = apic_base_msr.high;

	low |= IA32_APIC_BASE_MSR_ENABLE;

	cpu_write_msr(IA32_APIC_BASE_MSR, low, high);
}

uint32_t read_lapic_register(int offset) {
	return *(uint32_t*)(APIC_PHYSICAL_ADDRESS + offset);
}

void write_lapic_register(int offset, uint32_t data) {
	*(uint32_t*)(APIC_PHYSICAL_ADDRESS + offset) = data;
}

void send_lapic_eoi() {
    write_lapic_register(APIC_EOI_REG, 0);
}

void initialize_lapic() {
    get_apic_base();
	enable_apic_base();

	// configure spurious interrupts
	uint32_t lapic_spurious_int = read_lapic_register(APIC_SPURIOUS_INT_REG);
	lapic_spurious_int |= 0xff;		// sets dummy interrupt vector
	lapic_spurious_int |= (1<<8);	// sets enable-bit
	write_lapic_register(APIC_SPURIOUS_INT_REG, lapic_spurious_int);
}