#ifndef IDT_H
#define IDT_H

#include <stdbool.h>
#include <stdint.h>

#define GDT_KERNEL_CODE_SELECTOR (0x01 << 3)

// interrupt gate descriptor type
enum idt_gate_type {
    task = 0x5,
    int_16 = 0x6,
    trap_16 = 0x7,
    int_32 = 0xe,
    trap_32 = 0xf
};
typedef enum idt_gate_type idt_gate_type_t;

// struct idt_segment_selector {
//     int rpl : 2;    /* Requested Priveledge Level */
//     int ti : 1;     /* TI GDT=0, LDT=1*/
//     int index : 13; /* Bits 3-15 of the index of the GDT/LDT (bottom 3bits are always 0 due to 8 byte alignment) */
// } __attribute__((packed));

// enum segments {
//     GDT_KERNEL_CODE_SELECTOR = (const struct idt_segment_selector){
//         .rpl = 0,
//         .ti = 0,
//         .index = 0x08
//     }
// };

struct idt_type_attributes {
    int reserved : 1;
    int dpl : 2; // cpu priveledge
    int present : 1; // MUST BE 1 TO BE ACTIVE
} __attribute__((packed));

struct idt_entry {
    uint16_t offset_low;
    uint16_t seg_selector;
    int IST : 3;
    uint8_t reserved;
    int gate_type : 4;
    struct idt_type_attributes type_attributes;
    uint16_t offset_middle;
    uint32_t offset_high;
    uint32_t zero;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    struct idt_entry* base;
};

__attribute__((aligned(0x10)))
static struct idt_entry idt[256];

static struct idt_ptr idtp;

// lidt instruction
void idt_load();

void idt_set_gate(uint8_t index, uint64_t offset, uint16_t segment_selector, int IST, idt_gate_type_t gate_type, int dpl) {
    struct idt_entry *gate = &(idt[index]);

    gate->offset_low = offset & 0xFFFF;
    gate->offset_middle = (offset >> 16) & 0xFFFF;
    gate->offset_high = offset >> 32;

    gate->seg_selector = segment_selector;
    gate->IST = IST;
    gate->gate_type = gate_type;

    gate->type_attributes.present = 1;
    gate->type_attributes.dpl = dpl;
    gate->type_attributes.reserved = 0;

    gate->reserved = 0;
    gate->zero = 0;
}

extern void* isr_stub_table[];

void idt_init() {
    idtp.base = (struct idt_ptr*)&idt[0];
    idtp.limit = (uint16_t)sizeof(idt) * 256 - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_gate(vector, isr_stub_table[vector], GDT_KERNEL_CODE_SELECTOR, 0, int_32, 0);
    }

    __asm__ volatile ("lidt %0" : : "m"(idtp)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}

#endif