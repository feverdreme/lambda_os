#include <libc/fonts.h>
#include <libc/string.h>
#include <libc/typedef.h>
#include "graphics/putpixel.h"
#include "afterboot/gdt.h"
// #include "graphics/puts.h"
#include <stdbool.h>
#include "graphics/puts.h"
// #include <fonts/standard.h>
// #include <fonts/std_font.font.c>
// #include <libc/DEPREACTED_puts.h>

// idea, but magic number and append to end of kernel code as data so when read we know that's when to initiate paging
// simple scan scan scan until we find
// written in asm func implemetned
// everything is gonna be volatile lol
// extern _spleen_char_65;
// extern fontchar __spleen_char_37;

void main() {
    gdt_install();
    _init_spleen_font();
    // char* msg = "32 BIT MODE LETS GO\n\tOh my god it supports\nnewline.\0";
    // puts(msg, strlen(msg));

    // if (finds(src, s) != strend(src)){
    //     putrect(40, 30, 60, 120, 4);
    // }

    // if (_spleen_font.fc_width == 5
    // && _spleen_font.fc_height == 8
    // && (fontchar*)_spleen_font.data[0x41] != 0
    // ){
    //     putrect(200, 30, 60, 120, 4);
    // }
    // putc('A', &_spleen_font);
    // puts("Hello! this works!\n:)", &_spleen_font);
    // puts("\n", &_spleen_font);

    // puts("Marc@lambda_os$ whoami\n> Our esteemed dean of students", &_spleen_font);
    puts("Guess who has all the fonts correct... this guy!\nIt even supports newline\nAnd numbers... 123456789\nAnd symbols... -[@$(*%^&(#:>:}>", &_spleen_font);

    // struct font *fnt = &_spleen_font;
    // // char c = 'A';

    // // struct Cursor cursor = {0, 0, 2};

    // fontchar fc = _spleen_font.data['A'];
    // itoa(sizeof(fontchar*), bf, 10);
    // puts(bf, 10);
    // for (int i=0; i<25; i++){
    //     itoa(*(int*)_spleen_font.data[i], bf, 10);
    //     puts(bf, 10);
    //     puts("\n", 1);
    // }

    // for (int row = 0; row < fnt->fc_height; row++) {
    //     // itoa(fc[row], bf, 10);
    //     // puts(bf, 10);
    //     // puts("\n", 1);

    //     for (int col = 0; col < fnt->fc_width; col++) {
    //         // putpixel(col, row, (col + row) % 16);

    //         // if (fc == 0) continue;
    //         // putpixel(col, row, 7);
            
    //         // FIXME: Only works with bitmaps fonts with 16bit widths at most
    //         // bool drawbit = (*fc + sizeof(byte*) * 16) & 
    //         int drawbit = fc[row] & (1 << (8 - col));
    //         // // itoa(__spleen_char_37[row], bf, 10);
    //         // // puts(bf, 5); 

    //         if (drawbit) putpixel(col, row, 2);
    //     }
    // }

    // putc(A);
    // putc(B);
    // putc(C);
    // putc(D);
    // putc(A);

    return;
}