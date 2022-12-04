#ifndef PUTS_H
#define PUTS_H

#include <libc/fonts.h>

struct Cursor {
    int x, y;
    int prev_x;
    int kerning;
};

extern struct Cursor cursor;
extern const font_t *DEFAULT_FONT;

/*
    k-functions allow a font input
    reg functions default to spleen font
*/

int kputc(char c, int pos_x, int pos_y, font_t *fnt);
int kputs(char *c, int pos_x, int pos_y, font_t *fnt);
int kputd(int d, int pos_x, int pos_y, font_t *fnt);

int putc(char c, int pos_x, int pos_y);
int puts(char *c, int pos_x, int pos_y);
int putd(int d, int pos_x, int pos_y);

int kprintc(char c, font_t *fnt);
int kprints(char *c, font_t *fnt);
int kprintd(int d, font_t *fnt);

int printc(char c);
int prints(char *c);
int printd(int d);

int println();

#endif