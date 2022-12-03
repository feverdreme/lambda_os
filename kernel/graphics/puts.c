// TODO: Add makefile support
#include "puts.h"

#include <libc/fonts.h>
#include <libc/string.h>
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
        fontchar fc = ctofc(*c, fnt);

        if (*c == '\n') {
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
        if (pos_x == 0) // FIXME: pos_x will not always be 0 because of kerning: you must add a check to see if pos_x < prev_pos_x
            pos_y += 8 + cursor.kerning;
        else
            pos_x += cursor.kerning;
    }

    return 0;
}

int putd(int d, int pos_x, int pos_y, struct font *fnt) {
    char buf[21];
    itoa(d, buf);
    puts(buf, pos_x, pos_y, fnt);

    return 0;
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
    
    return 0;
}

int prints(char *c, struct font *fnt) {
    for (; *c != '\0'; c++) printc(*c, fnt);

    return 0;
}

int printd(int d, struct font *fnt) {
    char buf[21]; // max we'll need
    itoa(d, buf);

    prints(buf, fnt);
}

int println() {
    printc('\n', &spleen_font);
}