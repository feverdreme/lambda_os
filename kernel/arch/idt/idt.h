#ifndef IDT_H
#define IDT_H

#include <stdbool.h>
#include <stdint.h>

// interrupt gate descriptor type
enum idt_gate_type {
    task = 0x5,
    int_16 = 0x6,
    trap_16 = 0x7,
    int_32 = 0xe,
    trap_32 = 0xf
};
typedef enum idt_gate_type idt_gate_type_t;

struct segment_selector {
    int rpl : 2;
    int ti : 1;
    int index : 13;
} __attribute__((packed));

struct idt_type_attributes {
    int gate_type : 4;
    int reserved : 1;
    int dpl : 2; // cpu priveledge
    int present : 1; // MUST BE 1 TO BE ACTIVE
} __attribute__((packed));

struct idt_entry {
    uint16_t offset_low;
    struct segment_selector seg_selector;
    uint8_t reserved;
    struct idt_type_attributes type_attributes;
    uint16_t offset_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t idt_size;
    struct idt_entry* idt_location;
};

struct idt_entry idt[256]; 
struct idt_ptr idtp;

// lidt instruction
void idt_load();

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

// extern void* isr_stub_table[];

void idt_init() {
    // set the gates
    // idtp.idt_size = sizeof(struct idt_entry) * 256 - 1;
    // idtp.idt_location = &idt;

    // prepare for lidt
    idt_load();
}

#endif