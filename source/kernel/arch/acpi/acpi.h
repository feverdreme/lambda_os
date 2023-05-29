#ifndef ACPI_H
#define ACPI_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct ACPI_SDT_Header {
    char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    char OEMID[6];
    char OEMTableID[8];
    uint32_t OEM_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
} __attribute__((packed)) ACPI_SDT_Header_t;

typedef struct RSDP_Descriptor {
    char signature[8];
    uint8_t checksum;
    char OEMID[6];
    uint8_t revision;
    uint32_t rsdt_address;
} __attribute__((packed)) RSDP_Descriptor_t;

typedef struct Extended_RSDP_Descriptor {
    char signature[8];
    uint8_t checksum;
    char OEMID[6];
    uint8_t revision;
    uint32_t rsdt_address;
    
    // New in revision 2
    uint32_t length;
    uint64_t xsdt_address;
    uint8_t extended_checksum;
    uint8_t reserved[3];
} __attribute__ ((packed)) Extended_RSDP_Descriptor_t;

typedef struct RSDT {
    ACPI_SDT_Header_t header;
    uint32_t SDT_pointers[];    // NOTE: MUST BE CAST TO ADDRESS, DO NOT INDEX DIRECTLY
} RSDT_t;

/**
 * @brief Discovers what type of RSDP we're using.
 * 
 * @return int The revision number of the RSDP.
 */
int detect_rsdp_revision();

/**
 * @brief Locates the RSDT from the RSDP
 * 
 * @return void* 
 */
RSDT_t* find_rsdt();

/**
 * @brief Finds the desired SDT based on the signature.
 * 
 * @param rsdt_addr Pointer to the RSDT
 * @return void* The address of the SDT.
 */
void *find_sdt(const char *signature);

#ifdef __cplusplus
}
#endif
#endif