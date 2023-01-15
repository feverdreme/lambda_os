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

extern BOOTBOOT bootboot;               // see bootboot.h
extern unsigned char environment[4096]; // configuration, UTF-8 text key=value pairs
extern uint8_t fb;                      // linear framebuffer mapped 

// TODO: make libc and fonts shared static libraries to be linked last

void main() {
    // gdt_install();
    // idt_init();

    int x, y, s=bootboot.fb_scanline, w=bootboot.fb_width, h=bootboot.fb_height;

    if(s) {
        // cross-hair to see screen dimension detected correctly
        for(y=0;y<h;y++) { *((uint32_t*)(&fb + s*y + (w*2)))=0x00FFFFFF; }
        for(x=0;x<w;x++) { *((uint32_t*)(&fb + s*(h/2)+x*4))=0x00FFFFFF; }

        // red, green, blue boxes in order
    //     for(y=0;y<20;y++) { for(x=0;x<20;x++) { *((uint32_t*)(&fb + s*(y+20) + (x+20)*4))=0x00FF0000; } }
    //     for(y=0;y<20;y++) { for(x=0;x<20;x++) { *((uint32_t*)(&fb + s*(y+20) + (x+50)*4))=0x0000FF00; } }
    //     for(y=0;y<20;y++) { for(x=0;x<20;x++) { *((uint32_t*)(&fb + s*(y+20) + (x+80)*4))=0x000000FF; } }
    }

    putrect(30, 30, 100, 50, 0x00FF0000);
    // putrect(30, 100, 100, 50, 0x00FF00FF);

    // kputc('H', 0, 0, DEFAULT_FONT, 0x00FFFFFF);
    const char* t = "Hello World";
    prints("Kernel PANIC: ");
    // kpanic("Poggers");

    printd(bootboot.fb_height);

    return;

    // init_spleen_font();
    // init_mem_model();
    // init_genesis_window();

    // Window_t* test_window = create_window(0, 0, 320 / 2, 200, "Window 1", 20, BLACK, "Hello! test window!");
    // Window_t* test_window2 = create_window(320 / 2, 0, 320 / 2, 200 / 2, "Window 2", 20, BLACK, "Pog Pog");
    // Window_t* test_window3 = create_window(320 / 2, 200 / 2, 320 / 2, 200 / 2, "Patricie Viewer", 20, BLACK, "Ancilla est in foro");

    // window_draw_window(test_window);
    // window_draw_window(test_window2);
    // window_draw_window(test_window3);

    return;
}