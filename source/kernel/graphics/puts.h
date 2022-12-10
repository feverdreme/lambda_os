#ifndef PUTS_H
#define PUTS_H

#include <libc/fonts.h>
#include <graphics/putpixel.h>

struct Cursor {
    int x, y;
    int prev_x;
    int kerning;
    enum VGA_COLOR color;
};

extern struct Cursor cursor;
extern font_t *DEFAULT_FONT;

/*
    k-functions allow a font input
    reg functions default to spleen font
*/

int kputc(char c, int pos_x, int pos_y, font_t *fnt, enum VGA_COLOR color);
int kputs(const char *c, int pos_x, int pos_y, font_t *fnt, enum VGA_COLOR color);
int kputd(int d, int pos_x, int pos_y, font_t *fnt, enum VGA_COLOR color);

int putc(char c, int pos_x, int pos_y, enum VGA_COLOR color);
int puts(const char *c, int pos_x, int pos_y, enum VGA_COLOR color);
int putd(int d, int pos_x, int pos_y, enum VGA_COLOR color);

int kprintc(char c, font_t *fnt);
int kprints(const char *c, font_t *fnt);
int kprintd(int d, font_t *fnt);

int printc(char c);
int prints(const char *c);
int printd(int d);

int println();

#endif