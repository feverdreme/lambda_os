#include "apic.h"

#include <arch/msr.h>

#define IA32_APIC_BASE_MSR	0x1B

uint64_t get_apic_base() {
    MSR_Response_t apic_base_msr = cpu_read_msr(IA32_APIC_BASE_MSR);

	uint64_t apic_addr = (apic_base_msr.low & 0xfffff000) | ((uint64_t)apic_base_msr.high << 32);

	return apic_addr;
}