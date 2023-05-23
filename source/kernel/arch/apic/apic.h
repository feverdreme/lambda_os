#ifndef APIC_H
#define APIC_H

#include <stdint.h>

/**
 * @brief Get the apic physical address.
 * 
 * @return uint64_t 
 */
uint64_t get_apic_base();

#endif