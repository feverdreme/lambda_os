#include <envvars.h>

#include <libc/libc.h>

#include <memory/kmalloc.h>
#include <graphics/putpixel.h>
#include <graphics/puts.h>
#include <arch/gdt/gdt.h>
#include <arch/idt/idt.h>
#include <arch/debug/kpanic.h>

#include <wmgr/window.h>

#include <stdbool.h>

// TODO: make libc and fonts shared static libraries to be linked last

void main() {
    gdt_install();
    idt_init();
    init_spleen_font();
    init_mem_model();
    init_genesis_window();

    Window_t* test_window = create_window(0, 0, 320 / 2, 200, "Window 1", 20, BLACK, "Hello! test window!");
    Window_t* test_window2 = create_window(320 / 2, 0, 320 / 2, 200 / 2, "Window 2", 20, BLACK, "Pog Pog");
    Window_t* test_window3 = create_window(320 / 2, 200 / 2, 320 / 2, 200 / 2, "Window 3", 20, BLACK, "there's 3 now");

    window_draw_window(test_window);
    window_draw_window(test_window2);
    window_draw_window(test_window3);

    return;
}