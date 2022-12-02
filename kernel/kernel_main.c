#include <libc/fonts.h>
#include <libc/string.h>
#include <libc/typedef.h>

#include "memory/kmalloc.h"
#include "graphics/putpixel.h"
#include "graphics/puts.h"
#include "arch/gdt/gdt.h"
#include "arch/idt/idt.h"

#include <wmgr/window.h>

#include <stdbool.h>

void main() {
    gdt_install();
    idt_init();
    init_spleen_font();
    init_mem_model();

    struct memblock* mb = kmalloc(41);
    *(int*)(mb->data) = 0x0000000F;

    char buf[200];
    itoa(*(int*)(mb->data), buf);

    puts(buf, &spleen_font);
    puts("\n", &spleen_font);

    struct memblock* mb2 = kmalloc(40);
    char buf2[200];
    itoa(MEMROOT, buf2);
    puts(buf2, &spleen_font);

    // puts("Guess who has all the fonts correct... this guy!\nIt even supports newline\nAnd numbers... 123456789\nAnd symbols... -[@$(*%^&(#:>:}>", &spleen_font);

    return;
}