#include <stdint.h>
#include <stdbool.h>
#include <bootboot.h>

#include <envvars.h>
// #include <libc/libc.h>
#include <memory/kmalloc.h>
#include <graphics/putpixel.h>
#include <graphics/puts.h>
// #include <arch/gdt/gdt.h>
// #include <arch/idt/idt.h>
#include <arch/debug/kpanic.h>
// #include <wmgr/window.h>

// TODO: make libc and fonts shared static libraries to be linked last

void main() {
    // gdt_install();
    // idt_init();
    init_mem_model();
    init_genesis_window();

    // putrect(30, 30, 100, 50, 0x00FF0000);
    // putrect(30, 100, 100, 50, 0x00FF00FF);

    // kputc('H', 0, 0, DEFAULT_FONT, 0x00FFFFFF);
    // const char* t = "Hello World";

    // prints("Kernel PANIC: ");
    // kpanic("Poggers");

    // int* k = kmalloc(sizeof(int) * 15);

    // *(int*)k = 33;
    // // *(int*)(0xE000) = 33;
    // // printd(*(int*)(0xE000));
    // // *(k + 1) = '\0';
    // printd(*k);
    // int m = 0;
    // int* mptr = &m;
    // printd(mptr);
    // putrect(30, 30, 100, 50, 0x00FF00FF);

    // prints(k);
    // printc('H');
    // printd(&fb);

    // return;

    // init_spleen_font();
    // init_mem_model();


    // Window_t* test_window = create_window(0, 0, 320 / 2, 200, "Window 1", 20, BLACK, "Hello! test window!");
    // Window_t* test_window2 = create_window(320 / 2, 0, 320 / 2, 200 / 2, "Window 2", 20, BLACK, "Pog Pog");
    // Window_t* test_window3 = create_window(320 / 2, 200 / 2, 320 / 2, 200 / 2, "Patricie Viewer", 20, BLACK, "Ancilla est in foro");

    // window_draw_window(test_window);
    // window_draw_window(test_window2);
    // window_draw_window(test_window3);

    return;
}