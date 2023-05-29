#include "keyboard.h"

#include <arch/idt/idt.h>
#include <arch/apic/apic.h>
#include <arch/apic/ioapic.h>
#include <graphics/puts.h>
#include <memory/mem.h>

__attribute__((interrupt))
void keyboard_handler(interrupt_frame_t* frame) {
    // __asm__ volatile ("movl $0xdeadbeef, %ebx");
    unsigned char scan_code = inb(0x60);
    printd(scan_code);
    println();

    send_lapic_eoi();
}

void isr_keyboard_register() {
    idt_register_isr(33, &keyboard_handler);
    ioapic_write_entry(1, 33, IOREDTBL_FIXED, get_lapic_id());
}