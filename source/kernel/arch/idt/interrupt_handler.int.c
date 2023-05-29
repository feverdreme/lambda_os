#include <arch/idt/isr.h>
#include <arch/debug/kpanic.h>

__attribute__((interrupt))
void interrupt_handler(interrupt_frame_t* frame) {
    kpanic("Interrupted");
    __asm__ volatile ("cli; hlt");
}