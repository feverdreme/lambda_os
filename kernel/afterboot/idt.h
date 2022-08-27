#ifndef IDT_H
#define IDT_H

#include <stdbool.h>
#include <stdint.h>

extern struct gdt_entry gdt[3];

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

enum seg_selectors {
    GDT_CS_0 = (uint16_t)(&gdt[1] << 3 + 0b100);
    GDT_DS_0 = (uint16_t)(&gdt[2] << 3 + 0b100);
};

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
extern void idt_load();

void idt_set_gate(uint8_t index, uint32_t offset, struct segment_selector seg, idt_gate_type_t gate_type, uint8_t dpl, uint8_t present);

void idt_init();

#endif