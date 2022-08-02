#ifndef PUTS_H
#define PUTS_H

#include <libc/fonts.h>

struct Cursor {
    int x, y;
    int kerning;
};

// returns the error code: 0 for succ and 1 for fail
int putc(char c, struct font *fnt);
void puts(char *c, struct font *fnt);

#endif