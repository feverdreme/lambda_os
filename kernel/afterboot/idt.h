#ifndef IDT_H
#define IDT_H

// interrupt gate descriptor type
enum igt_gate_type {
    task = 0x5,
    int_16 = 0x6,
    trap_16 = 0x7,
    int_32 = 0xe,
    trap_32 = 0xf
};

struct idt_type_attributes {
    int gate_type : 4;
    int reserved : 1;
    int dpl : 2; // cpu priveledge
    int present : 1; // MUST BE 1 TO BE ACTIVE
} __attribute__((packed));

struct idt_entry {
    uint16_t offset_low;
    uint16_t seg_selector;
    uint8_t reserved;
    struct idt_type_attributes type_attributes;
    uint16_t offset_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    struct idt_entry* base;
};

struct idt_entry idt[256]; 
struct idt_ptr idtp;

// lidt instruction
extern void register_idt();

void idt_set_gate();
void idt_install();

#endif