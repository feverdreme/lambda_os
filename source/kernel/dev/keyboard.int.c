#include "keyboard.h"

#include <arch/idt/idt.h>
#include <arch/apic/apic.h>
#include <arch/apic/ioapic.h>
#include <graphics/puts.h>

__attribute__((interrupt))
void keyboard_handler(interrupt_frame_t* frame) {
    // __asm__ volatile ("movl $0xdeadbeef, %ebx");
    prints("KEYBOARD\n");
}

void isr_keyboard_register() {
    idt_register_isr(33, &keyboard_handler);

    ioapic_write_entry(1, 33, IOREDTBL_FIXED, read_lapic_register(0x20));
    printh(ioapic_read_entry(1));
    println();
}