// TODO: Add makefile support
#include <fonts/standard.h>
#include "putpixel.h"

typedef struct {
    int x, y, w, h;
    int kerning;
} cursor;

cursor Cursor = {0, 0, 1, 1, 2};

void putc(p_char c) {
    for (int row=0; row<8; row++) {
        for (int col=0; col<8; col++) {
            if (c[row][col] != '#') continue;

            putrect(Cursor.x + Cursor.w * col,
                    Cursor.y + Cursor.h * row,
                    Cursor.w,
                    Cursor.h,
                    15);
        }
    }

    Cursor.x += Cursor.kerning + 8 * Cursor.w;
}

// void puts(char *c) {

// }