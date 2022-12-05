#include <envvars.h>

#include <libc/libc.h>

#include <memory/kmalloc.h>
#include <graphics/putpixel.h>
#include <graphics/puts.h>
#include <arch/gdt/gdt.h>
#include <arch/idt/idt.h>
#include <arch/debug/kpanic.h>

// #include <wmgr/window.h>

#include <stdbool.h>

// TODO: make libc and fonts shared static libraries to be linked last

void main() {
    gdt_install();
    idt_init();
    init_spleen_font();
    init_mem_model();

    return;
}