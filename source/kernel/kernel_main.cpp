#include <stdint.h>
#include <stdbool.h>
#include <limine.h>

#include <envvars.h>

#include <arch/idt/idt.h>
#include <arch/apic/apic.h>
#include <arch/acpi/madt.h>
#include <arch/apic/ioapic.h>

// #include <arch/cpuid_query.h>
#include <memory/kmalloc.h>
#include <memory/mem.h>
#include <memory/pmm/pmm.h>
#include <graphics/fb.h>
#include <graphics/putpixel.h>
#include <graphics/puts.h>
#include <arch/debug/kpanic.h>
#include <wmgr/window.hpp>
// #include <wmgr/tile.h>
#include <memory/paging/paging.h>
#include <dev/keyboard.h>

// TODO: make libc and fonts shared static libraries to be linked last

extern "C" {
void main() {
    initialize_fb();
    idt_init();
    pmm_init();
    initialize_paging();
    init_mem_model();
    initialize_lapic();
    ioapic_init();
    isr_keyboard_register();

    inb(0x60);

    putrect(0, 0, FB_WIDTH, FB_HEIGHT, BLACK);

    // Tile_t *genesis_tile = init_genesis_tile();
    Window *w = new Window(0, 0, FB_WIDTH, FB_HEIGHT, "Shell", LIGHTCYAN, BLACK);
    w->draw();
    // __asm__ volatile("int $0x21");

    for(;;) {
        __asm__ volatile("hlt");
    }
    prints("\nPROGRAM FINISHED");

    return;
}
}