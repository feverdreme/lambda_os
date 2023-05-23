#ifndef ACPI_H
#define ACPI_H

#include <stdint.h>

typedef struct RSDP_Descriptor {
    char signature[8];
    uint8_t checksum;
    char OEMID[6];
    uint8_t revision;
    uint32_t rsdt_address;
} __attribute__ ((packed)) RSDP_Descriptor_t;
/**
 * @brief Discovers what type of RSDP we're using.
 * 
 * @return int The revision number of the RSDP.
 */
int detect_rsdp_revision();

#endif