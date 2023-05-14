#include "idt.h"

void idt_set_gate(uint8_t index, uint64_t offset, uint16_t segment_selector,
                  int IST, uint8_t gate_type, int type_attributes) {
    struct idt_entry *gate = &(idt[index]);

    gate->offset_low = offset & 0xFFFF;
    gate->offset_middle = (offset >> 16) & 0xFFFF;
    gate->offset_high = offset >> 32;

    gate->seg_selector = segment_selector;
    gate->IST = IST;
    gate->gate_type = gate_type;

    gate->type_attributes = type_attributes;

    gate->reserved = 0;
    gate->zero = 0;
}

void idt_init() {
    idtp.base = (struct idt_ptr *)&idt[0];
    idtp.limit = (uint16_t)sizeof(idt) * 256 - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_gate(vector, isr_stub_table[vector], GDT_KERNEL_CODE_SELECTOR,
                     0, IDT_INT32_GATE, IDT_DPL_RING0);
    }

    __asm__ volatile("lidt %0" : : "m"(idtp));  // load the new IDT
    __asm__ volatile("sti");                    // set the interrupt flag
}
