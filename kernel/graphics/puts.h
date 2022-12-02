#ifndef PUTS_H
#define PUTS_H

#include <libc/fonts.h>

struct Cursor {
    int x, y;
    int kerning;
};

int putc(char c, int pos_x, int pos_y, struct font *fnt);
int printc(char c, struct font *fnt);
int prints(char *c, struct font *fnt);

#endif