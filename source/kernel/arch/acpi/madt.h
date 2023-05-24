#ifndef MADT_H
#define MADT_H

#include <arch/acpi/acpi.h>

#define MADT_SIGNATURE  "APIC"

typedef struct MADT_Entry {
    uint8_t type;
    uint8_t length;
    uint8_t *data;
} __attribute__((packed)) MADT_Entry_t;

typedef struct MADT {
    ACPI_SDT_Header_t header;
    uint32_t lapic_address;
    uint32_t flags;
    MADT_Entry_t *entries;
} __attribute__((packed)) MADT_t;

typedef struct MADT_LAPIC_DESCRIPTOR {
    uint8_t acpi_processor_id;
    uint8_t apic_id;
    uint32_t flags;
} __attribute__((packed)) MADT_LAPIC_DESCRIPTOR_t;

typedef struct MADT_IOAPIC_DESCRIPTOR {
    uint8_t ioapic_id;
    uint8_t reserved;
    uint8_t ioapic_address;
    uint8_t gsi_base;
} __attribute__((packed)) MADT_IOAPIC_DESCRIPTOR_t;

typedef struct MADT_IOAPIC_IRQ_OVERRIDE_DESCRIPTOR {
    uint8_t bus_source;
    uint8_t irq_source;
    uint32_t gsi;
    uint16_t flags;
} __attribute__((packed)) MADT_IOAPIC_IRQ_OVERRIDE_DESCRIPTOR_t;

typedef struct MADT_IOAPIC_NMI_DESCRIPTOR {
    uint8_t nmi_source;
    uint8_t reserved;
    uint16_t flags;
    uint32_t gsi;
} __attribute__((packed)) MADT_IOAPIC_NMI_DESCRIPTOR_t;

typedef struct MADT_LAPIC_NMI_DESCRIPTOR {
    uint8_t acpi_processor_id;
    uint16_t flags;
    uint8_t lint;
} __attribute__((packed)) MADT_LAPIC_NMI_DESCRIPTOR_t;

typedef struct LAPIC_OVERRIDE_DESCRIPTOR {
    uint16_t reserved;
    uint32_t lapicx2_id;
    uint32_t flags;
    uint32_t acpi_id;
} __attribute__((packed)) LAPIC_OVERRIDE_DESCRIPTOR_t;

/**
 * @brief Locates the MADT.
 * 
 * @return MADT_t* The address to the MADT.
 */
MADT_t *find_madt();

#endif