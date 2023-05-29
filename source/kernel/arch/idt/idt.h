#ifndef IDT_H
#define IDT_H

#include <stdbool.h>
#include <stdint.h>

#define IDT_INTERRUPT_GATE  0xE
#define IDT_TRAP_GATE       0xF
#define IDT_PRESENT         (1<<7)

#define IDT_DPL_RING0       (0x0 << 5)
#define IDT_DPL_RING3       (0x3 << 5)
#define IDT_PRESENT_FLAG    0b1000        

#define GDT_KERNEL_CODE_SELECTOR (0x05 * 8)  // Fifth index, entries are 8 bytes

typedef struct idt_gate {
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t IST;
    uint8_t attributes;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t reserved;
} __attribute__((packed)) idt_gate_t;

struct idt_ptr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

static struct idt_ptr idtp;

__attribute__((aligned(0x10)))
static idt_gate_t idt[256];

extern void* isr_stub_table[];

/**
 * @brief Fine-tuned control of the IDT entries.
 * 
 * @param index Index in the IDT.
 * @param offset 64bit address to the ISR.
 * @param segment_selector What segment selector to use.
 * @param IST Interrupt Stack Table
 * @param attributes Other Attributes
 */
void idt_set_gate(uint8_t index, uint64_t offset, uint16_t segment_selector, uint8_t IST, uint8_t attributes);

/**
 * @brief Configures an IDT entry for the ISR, as well as marking it present.
 * 
 * @param index 
 * @param offset 
 */
void idt_register_isr(uint8_t index, uint64_t offset);

void idt_init();

#endif