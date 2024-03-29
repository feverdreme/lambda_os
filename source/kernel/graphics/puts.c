#include "puts.h"

#include <envvars.h>
#include <graphics/putpixel.h>
#include <graphics/fb.h>
#include <graphics/vga_constants.h>

font_t *DEFAULT_FONT = &spleen_font;

Cursor_t cursor = {0, 0, 0, 1, GREEN};

int kputc(char c, int pos_x, int pos_y, font_t *fnt, pixel_color_t color) {
    // check if printable
    if (!fnt->is_printable[(ascii_code_t)c]) {
        return 1;
    }

    fontchar* fc = ctofc(c, fnt);

    if (c == '\n') return 0;

    // if (fnt->fc_width == 5) putrect(30, 100, 100, 50, 0x00FF00FF);

    for (uint8_t row = 0; row < fnt->fc_height; row++) {
        for (uint8_t col = 0; col < fnt->fc_width; col++) {
            // FIXME: Only works with bitmaps fonts with 16bit widths at most
            int drawbit = fc[row] & (1 << (8 - col));
            if (drawbit) putpixel(pos_x + col, pos_y + row, color);
        }
    }

    return 0;
}

int kputs(const char* c, int pos_x, int pos_y, font_t *fnt, pixel_color_t color) {
    int prev_pos_x = pos_x;

    for (; *c != '\0'; c++) {

        fontchar* fc = ctofc(*c, fnt);

        if (*c == '\n') {
            pos_x = 0;
            prev_pos_x = 0;
            pos_y += 8;
            continue;
        }

        else if (!fnt->is_printable[(ascii_code_t)(*c)]) {
            // TODO IMPLEMENT CONTROL CHARACTERS
            continue;
            
            kprintc(c, fnt);
        }
        
        // if it will write past the screen
        if (pos_x + fnt->fc_width >= FB_WIDTH) {
            // reset the counter while controlling vars
            pos_x = 0;
            prev_pos_x = 0;
            pos_y += 8;
        }

        for (uint32_t row = 0; row < fnt->fc_height; row++) {
            for (uint32_t col = 0; col < fnt->fc_width; col++) {
                // FIXME: Only works with bitmaps fonts with 16bit widths at
                // most
                int drawbit = fc[row] & (1 << (8 - col));
                if (drawbit) putpixel(pos_x + col, pos_y + row, color);
            }
        }

        pos_x += cursor.kerning;
        pos_x = (pos_x + fnt->fc_width) % FB_WIDTH;

        if (pos_x < prev_pos_x) {
            pos_x = 0;
            pos_y += fnt->fc_height + cursor.kerning;
        }

        prev_pos_x = pos_x;
    }

    return 0;
}

int kputd(int d, int pos_x, int pos_y, font_t *fnt, pixel_color_t color) {
    char buf[21];
    itoa(d, buf);
    return kputs(buf, pos_x, pos_y, fnt, color);
}

int putc(char c, int pos_x, int pos_y, pixel_color_t color) {
    return kputc(c, pos_x, pos_y, DEFAULT_FONT, color);
}

int puts(const char *c, int pos_x, int pos_y, pixel_color_t color) {
    return kputs(c, pos_x, pos_y, DEFAULT_FONT, color);
}

int putd(int d, int pos_x, int pos_y, pixel_color_t color) {
    return kputd(d, pos_x, pos_y, DEFAULT_FONT, color);
}


int kprintc(char c, struct font *fnt) {


    fontchar* fc = ctofc(c, fnt);

    if (c == '\n') {
        cursor.x = 0;
        cursor.prev_x = 0;
        cursor.y += 8;
        return 0;
    }

    if (!fnt->is_printable[(ascii_code_t)c]) return 1;
    
    // if it will write past the screen
    if (cursor.x + fnt->fc_width >= FB_WIDTH) {
        // reset the counter while controlling vars
        cursor.x = 0;
        cursor.prev_x = 0;
        cursor.y += 8;
    }
    cursor.y %= FB_HEIGHT;

    for (uint64_t row = 0; row < fnt->fc_height; row++) {
        for (uint64_t col = 0; col < fnt->fc_width; col++) {
            // FIXME: Only works with bitmaps fonts with 16bit widths at
            // most
            int drawbit = fc[row] & (1 << (8 - col));
            if (drawbit) putpixel(cursor.x + col, cursor.y + row, cursor.color);
        }
    }

    cursor.x += cursor.kerning;
    cursor.x = (cursor.x + fnt->fc_width) % FB_WIDTH;

    if (cursor.x < cursor.prev_x) {
        cursor.y += fnt->fc_width + cursor.kerning;
        cursor.x = 0;
    }

    cursor.prev_x = cursor.x;
    return 0;
}

int kprints(const char *c, font_t *fnt) {
    for (; *c != '\0'; c++) kprintc(*c, fnt);

    return 0;
}

int kprintd(uint64_t d, font_t *fnt) {
    char buf[31]; // max we'll need
    itoa(d, buf);

    return kprints(buf, fnt);
}

int kprinth(uint64_t h, font_t *fnt) {
    char buf[31]; // max we'll need
    hex(h, buf);

    return kprints(buf, fnt);
}

int printc(char c) {
    return kprintc(c, DEFAULT_FONT);
}

int prints(const char *c) {
    return kprints(c, DEFAULT_FONT);
}

int printd(uint64_t d) {
    return kprintd(d, DEFAULT_FONT);
}

int printh(uint64_t h) {
    return kprinth(h, DEFAULT_FONT);
}

int println() {
    return kprintc('\n', DEFAULT_FONT);
}