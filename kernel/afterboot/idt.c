#include "idt.h"

void idt_set_gate(uint8_t index, uint32_t offset, int ss_rpl : 2, int ss_ti : 1, int ss_index : 13, enum idt_gate_type gate_type, int dpl : 2, int present : 1) {
    struct idt_entry *gate = &(idt[index]);

    gate->offset_low = offset & 0xFFFF;
    gate->offset_high = offset >> 16;
    gate->seg_selector = seg_selector;
    gate->reserved = 0;

    gate->type_attributes.gate_type = gate_type;
    gate->type_attributes.dpl = dpl;
    gate->type_attributes.present = present;
    gate->type_attributes.reserved = 0;
}

void idt_init() {
    // set the gates

    // prepare for lidt


}