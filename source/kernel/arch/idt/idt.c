#include "idt.h"

void idt_set_gate(uint8_t index, uint64_t offset, uint16_t segment_selector, uint8_t IST, uint8_t attributes) {
    idt_gate_t *gate = &(idt[index]);

    gate->offset_low = offset & 0xFFFF;
    gate->offset_mid = (offset >> 16) & 0xFFFF;
    gate->offset_high = offset >> 32;
    gate->segment_selector = segment_selector;
    gate->IST = IST & 0b111;
    gate->attributes = attributes;
    gate->reserved = 0;
}

void idt_register_isr(uint8_t index, uint64_t offset) {
    idt_set_gate(index,
                offset,
                GDT_KERNEL_CODE_SELECTOR,
                IDT_DPL_RING0,
                IDT_INTERRUPT_GATE | IDT_PRESENT);
}

void idt_init() {
    idtp.limit = (uint16_t)sizeof(idt_gate_t) * 256 - 1;
    idtp.base = (uint64_t)(&idt[0]);

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_register_isr(vector, isr_stub_table[vector]);
    }

    __asm__ volatile("lidt %0" : : "m"(idtp));  // load the new IDT
    __asm__ volatile("sti");                    // set the interrupt flag
}
