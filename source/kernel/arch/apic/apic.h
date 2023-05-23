#ifndef APIC_H
#define APIC_H

#include <stdint.h>

#define IA32_APIC_BASE_MSR	        0x1B
#define IA32_APIC_BASE_MSR_ENABLE   (1<<11)
#define IA32_APIC_BASE_MSR_BSP      (1<<8)

#define APIC_SPURIOUS_INT_REG       0xF0

extern uint64_t APIC_PHYSICAL_ADDRESS;

/**
 * @brief Get the apic physical address. Side-effect: sets APIC_PHYSICAL_ADDRESS
 * 
 * @return uint64_t 
 */
uint64_t get_apic_base();

/**
 * @brief Sets the enable flag on the APIC MSR.
 * 
 */
void enable_apic_base();

/**
 * @brief Reads a LAPIC register at resignated offset.
 * 
 * @param offset 
 * @return uint32_t 
 */
uint32_t read_lapic_register(int offset);

/**
 * @brief Writes to a LAPIC register.
 * 
 * @param offset 
 * @param data 
 */
void write_lapic_register(int offset, uint32_t data);

/**
 * @brief Initializes the Local APIC.
 * 
 */
void initialize_lapic();

#endif