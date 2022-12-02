// TODO: Add makefile support
#include "puts.h"

#include <libc/fonts.h>
#include <stdbool.h>

#include "putpixel.h"

struct Cursor cursor = {0, 0, 1};

int putc(char c, int pos_x, int pos_y, struct font* fnt) {
    fontchar fc = ctofc(c, fnt);

    if (c == '\n') return 0;
    if (fc == 0) return 1;

    for (int row = 0; row < fnt->fc_height; row++) {
        for (int col = 0; col < fnt->fc_width; col++) {
            // FIXME: Only works with bitmaps fonts with 16bit widths at most
            int drawbit = fc[row] & (1 << (8 - col));
            if (drawbit) putpixel(pos_x + col, pos_y + row, GREEN);
        }
    }

    return 0;
}

int puts(char* c, int pos_x, int pos_y, struct font *fnt) {
    for (; *c != '\0'; c++) {
        fontchar fc = ctofc(c, fnt);

        if (c == '\n') {
            pos_x = 0;
            pos_y += 8;
            return 0;
        }
        if (fc == 0) return 1;

        for (int row = 0; row < fnt->fc_height; row++) {
            for (int col = 0; col < fnt->fc_width; col++) {
                // FIXME: Only works with bitmaps fonts with 16bit widths at
                // most
                int drawbit = fc[row] & (1 << (8 - col));
                if (drawbit) putpixel(pos_x + col, pos_y + row, 2);
            }
        }

        pos_x = (pos_x + 5) % 320;
        if (pos_x == 0)
            pos_y += 8 + cursor.kerning;
        else
            pos_x += cursor.kerning;
    }
}

int printc(char c, struct font *fnt) {
    fontchar fc = ctofc(c, fnt);

    if (c == '\n') {
        cursor.x = 0;
        cursor.y += 8;
        return 0;
    }
    if (fc == 0) return 1;

    for (int row = 0; row < fnt->fc_height; row++) {
        for (int col = 0; col < fnt->fc_width; col++) {
            // FIXME: Only works with bitmaps fonts with 16bit widths at
            // most
            int drawbit = fc[row] & (1 << (8 - col));
            if (drawbit) putpixel(cursor.x + col, cursor.y + row, 2);
        }
    }

    cursor.x = (cursor.x + 5) % 320;
    if (cursor.x == 0)
        cursor.y += 8 + cursor.kerning;
    else
        cursor.x += cursor.kerning;
}

int prints(char *c, struct font *fnt) {
    for (; *c != '\0'; c++) putc(*c, fnt);

    return 0;
}