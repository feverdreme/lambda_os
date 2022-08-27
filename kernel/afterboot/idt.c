#include "idt.h"

void idt_set_gate(uint8_t index, uint32_t offset, struct segment_selector seg, idt_gate_type_t gate_type, uint8_t dpl, uint8_t present) {
    struct idt_entry *gate = &(idt[index]);

    gate->offset_low = offset & 0xFFFF;
    gate->offset_high = offset >> 16;
    gate->reserved = 0;

    gate->type_attributes.gate_type = gate_type;
    gate->type_attributes.dpl = dpl;
    gate->type_attributes.present = present;
    gate->type_attributes.reserved = 0;

    gate->seg_selector = seg;
}

void idt_init() {
    // set the gates

    // prepare for lidt
    idt_load();
}