#ifndef APIC_H
#define APIC_H

#include <stdint.h>

#define IA32_APIC_BASE_MSR	        0x1B
#define IA32_APIC_BASE_MSR_ENABLE   (1<<11)
#define IA32_APIC_BASE_MSR_BSP      (1<<8)

/**
 * @brief Get the apic physical address.
 * 
 * @return uint64_t 
 */
uint64_t get_apic_base();

/**
 * @brief Sets the enable flag on the APIC MSR.
 * 
 */
void enable_apic_base();

#endif