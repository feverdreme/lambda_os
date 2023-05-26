#include "madt.h"

#include <arch/debug/kdmsg.h>

void parse_madt() {
    MADT_t *madt = find_madt();

    MADT_Entry_t *madt_entry = &madt->entries;
    uint8_t *madt_entry_addr = (uint8_t*)madt_entry;

    while ((uint64_t)madt_entry < (uint64_t)madt + madt->header.length) {
        switch (madt_entry->type) {
            case 0:
                handle_lapic_descriptor(madt_entry);
            break;
            case 1:
                handle_ioapic_descriptor(madt_entry);
            break;
            case 2:
                handle_ioapic_irq_override_descriptor(madt_entry);
            break;
            case 3:
                handle_ioapic_nmi_descriptor(madt_entry);
            break;
            case 4:
                handle_lapic_nmi_descriptor(madt_entry);
            break;
            case 5:
                handle_lapic_override_descriptor(madt_entry);
            break;
            default:
                kdmsg("UNHANDLED MADT ENTRY");
            break;
        }

        madt_entry_addr += madt_entry->length;
        madt_entry = (MADT_t*)madt_entry_addr;
    }
}