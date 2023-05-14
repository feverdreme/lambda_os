#ifndef IDT_H
#define IDT_H

#include <stdbool.h>
#include <stdint.h>

#define IDT_TASK_GATE       0x5
#define IDT_INT16_GATE      0x6
#define IDT_TRAP16_GATE     0x7
#define IDT_INT32_GATE      0xE
#define IDT_TRAP32_GATE     0xF

#define IDT_DPL_RING0       (0x0 << 1)
#define IDT_DPL_RING3       (0x3 << 1)
#define IDT_PRESENT_FLAG    0b1000        

#define GDT_KERNEL_CODE_SELECTOR (0x03 * 8)  // Third index, entries are 8 bytes

struct idt_entry {
    uint16_t offset_low;
    uint16_t seg_selector;
    int IST : 3;
    uint8_t reserved;
    int gate_type : 4;
    int type_attributes : 4;
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

void idt_set_gate(uint8_t index, uint64_t offset, uint16_t segment_selector, int IST, uint8_t gate_type, int type_attributes);

extern void* isr_stub_table[];

void idt_init();

#endif