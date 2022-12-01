#include <libc/fonts.h>
#include <libc/string.h>
#include <libc/typedef.h>

#include "graphics/putpixel.h"
#include "arch/gdt/gdt.h"
#include "arch/idt/idt.h"
#include "graphics/puts.h"

#include <stdbool.h>

void main() {
    gdt_install();
    idt_load();
    init_spleen_font();

    puts("Guess who has all the fonts correct... this guy!\nIt even supports newline\nAnd numbers... 123456789\nAnd symbols... -[@$(*%^&(#:>:}>", &spleen_font);

    return;
}