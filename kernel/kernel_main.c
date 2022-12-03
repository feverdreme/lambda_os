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

    void* ptr = kmalloc(0x100);
    printd((int)ptr, &spleen_font);

    println();

    for (int i=0; i<18; i++){
        printd(MAT[i].memid, &spleen_font);
        printc(' ', &spleen_font);
    }

    println();

    char buf[21];
    itoa(-12345, buf);
    prints(buf, &spleen_font);
    // ptr = kmalloc(64);
    // *(int*)ptr = ceildiv(64, 16);
    // char buf[20];
    // itoa(*(int*)ptr, buf);

    // puts("hi", 39, 0, &spleen_font);
    // prints(buf, &spleen_font);
    // printc('\n', &spleen_font);
    // printd(53535, &spleen_font);
    // printc('\n', &spleen_font);
    // prints("\nHi2", &spleen_font);

    // prints(buf, &spleen_font);

    // puts("Guess who has all the fonts correct... this guy!\nIt even supports newline\nAnd numbers... 123456789\nAnd symbols... -[@$(*%^&(#:>:}>", &spleen_font);

    return;
}