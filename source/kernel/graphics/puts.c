// TODO: Add makefile support
#include "puts.h"

#include <libc/fonts.h>
#include <libc/string.h>
#include <stdbool.h>

#include "putpixel.h"

const font_t *DEFAULT_FONT = &spleen_font;

struct Cursor cursor = {0, 0, 0, 1};

int kputc(char c, int pos_x, int pos_y, font_t *fnt) {
    fontchar fc = ctofc(c, fnt);

    if (c == '\n') return 0;
    if (fc == NONPRINTABLE_FONTCHAR) return 1;

    for (int row = 0; row < fnt->fc_height; row++) {
        for (int col = 0; col < fnt->fc_width; col++) {
            // FIXME: Only works with bitmaps fonts with 16bit widths at most
            int drawbit = fc[row] & (1 << (8 - col));
            if (drawbit) putpixel(pos_x + col, pos_y + row, GREEN);
        }
    }

    return 0;
}

int kputs(char* c, int pos_x, int pos_y, font_t *fnt) {
    int prev_pos_x = pos_x;

    for (; *c != '\0'; c++) {
        fontchar fc = ctofc(*c, fnt);

        if (*c == '\n') {
            pos_x = 0;
            prev_pos_x = 0;
            pos_y += 8;
            continue;
        }
        if (fc == NONPRINTABLE_FONTCHAR) return 1;

        // if it will write past the screen
        if (pos_x + fnt->fc_width >= 320) {
            // reset the counter while controlling vars
            pos_x = 0;
            prev_pos_x = 0;
            pos_y += 8;
        }

        for (int row = 0; row < fnt->fc_height; row++) {
            for (int col = 0; col < fnt->fc_width; col++) {
                // FIXME: Only works with bitmaps fonts with 16bit widths at
                // most
                int drawbit = fc[row] & (1 << (8 - col));
                if (drawbit) putpixel(pos_x + col, pos_y + row, 2);
            }
        }

        pos_x += cursor.kerning;
        pos_x = (pos_x + fnt->fc_width) % 320;

        if (pos_x < prev_pos_x) {
            pos_x = 0;
            pos_y += 8 + cursor.kerning;
        }

        prev_pos_x = pos_x;
    }

    return 0;
}

int kputd(int d, int pos_x, int pos_y, font_t *fnt) {
    char buf[21];
    itoa(d, buf);
    kputs(buf, pos_x, pos_y, fnt);

    return 0;
}

int putc(char c, int pos_x, int pos_y) {
    kputc(c, pos_x, pos_y, DEFAULT_FONT);
}

int puts(char *c, int pos_x, int pos_y) {
    kputs(c, pos_x, pos_y, DEFAULT_FONT);
}

int putd(int d, int pos_x, int pos_y) {
    kputd(d, pos_x, pos_y, DEFAULT_FONT);
}


int kprintc(char c, struct font *fnt) {
    fontchar fc = ctofc(c, fnt);

    if (c == '\n') {
        cursor.x = 0;
        cursor.prev_x = 0;
        cursor.y += 8;
        return 0;
    }
    if (fc == NONPRINTABLE_FONTCHAR) return 1;

    // if it will write past the screen
    if (cursor.x + fnt->fc_width >= 320) {
        // reset the counter while controlling vars
        cursor.x = 0;
        cursor.prev_x = 0;
        cursor.y += 8;
    }

    for (int row = 0; row < fnt->fc_height; row++) {
        for (int col = 0; col < fnt->fc_width; col++) {
            // FIXME: Only works with bitmaps fonts with 16bit widths at
            // most
            int drawbit = fc[row] & (1 << (8 - col));
            if (drawbit) putpixel(cursor.x + col, cursor.y + row, 2);
        }
    }

    cursor.x += cursor.kerning;
    cursor.x = (cursor.x + fnt->fc_width) % 320;

    if (cursor.x < cursor.prev_x) {
        cursor.y += 8 + cursor.kerning;
        cursor.x = 0;
    }

    cursor.prev_x = cursor.x;
    
    return 0;
}

int kprints(char *c, font_t *fnt) {
    for (; *c != '\0'; c++) kprintc(*c, fnt);

    return 0;
}

int kprintd(int d, font_t *fnt) {
    char buf[21]; // max we'll need
    itoa(d, buf);

    kprints(buf, fnt);
}

int printc(char c) {
    kprintc(c, DEFAULT_FONT);
}

int prints(char *c) {
    kprints(c, DEFAULT_FONT);
}

int printd(int d) {
    kprintd(d, DEFAULT_FONT);
}

int println() {
    kprintc('\n', &spleen_font);
}