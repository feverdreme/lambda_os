#ifndef PUTS_H
#define PUTS_H

#include <libc/fonts.h>

struct Cursor {
    int x, y;
    int kerning;
};

extern struct Cursor cursor;

int putc(char c, int pos_x, int pos_y, struct font *fnt);
int puts(char *c, int pos_x, int pos_y, struct font *fnt);
int putd(int d, int pos_x, int pos_y, struct font *fnt);

int printc(char c, struct font *fnt);
int prints(char *c, struct font *fnt);
int printd(int d, struct font *fnt);
int println();

#endif