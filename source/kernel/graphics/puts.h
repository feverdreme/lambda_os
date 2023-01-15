#ifndef PUTS_H
#define PUTS_H

#include <libc/fonts.h>
#include <graphics/putpixel.h>

typedef struct Cursor {
    int x, y;
    int prev_x;
    int kerning;
    pixel_color_t color;
} Cursor_t;

extern Cursor_t cursor;
extern font_t *DEFAULT_FONT;

/*
    k-functions allow a font input
    reg functions default to spleen font
*/

int kputc(char c, int pos_x, int pos_y, font_t *fnt, pixel_color_t color);
int kputs(const char *c, int pos_x, int pos_y, font_t *fnt, pixel_color_t color);
int kputd(int d, int pos_x, int pos_y, font_t *fnt, pixel_color_t color);

int putc(char c, int pos_x, int pos_y, pixel_color_t color);
int puts(const char *c, int pos_x, int pos_y, pixel_color_t color);
int putd(int d, int pos_x, int pos_y, pixel_color_t color);

int kprintc(char c, font_t *fnt);
int kprints(const char *c, font_t *fnt);
int kprintd(int d, font_t *fnt);

int printc(char c);
int prints(const char *c);
int printd(int d);

int println();

#endif