#include <libc/fonts.h>
#include <libc/string.h>
#include <libc/typedef.h>
// #include "graphics/putpixel.h"
// #include "graphics/puts.h"
// #include <fonts/standard.h>
// #include <fonts/std_font.font.c>

// idea, but magic number and append to end of kernel code as data so when read we know that's when to initiate paging
// simple scan scan scan until we find
// written in asm func implemetned
// everything is gonna be volatile lol

void main() {
    // char* msg = "32 BIT MODE LETS GO\n\tOh my god it supports\nnewline.\0";
    // puts(msg, strlen(msg));
    const char* src = "Helo my name is ell Jeffrey\0";
    const char* s = "ell\0";

    // if (finds(src, s) != strend(src)){
    //     putrect(40, 30, 60, 120, 4);
    // }

    // putc(A);
    // putc(B);
    // putc(C);
    // putc(D);
    // putc(A);

    return;
}