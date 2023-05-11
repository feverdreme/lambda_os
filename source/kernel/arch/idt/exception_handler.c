#include <arch/debug/kpanic.h>

__attribute__((noreturn))
void exception_handler(void);
void exception_handler() {
    kpanic("Interrupted");
    __asm__ volatile ("cli; hlt");
}