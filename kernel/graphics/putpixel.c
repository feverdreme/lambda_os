#include "putpixel.h"

void putpixel(int pos_x, int pos_y, unsigned char vga_color) {
    volatile unsigned char* location = (volatile unsigned char*)0xA0000 + 320 * pos_y + pos_x;
    *location = VGA_COLOR;
}

void put_hline(int pos_x, int pos_y, int len, unsigned char vga_color) {
    volatile unsigned char* location = (volatile unsigned char*)0xA0000 + 320 * pos_y + pos_x;

    // Clamp len
    // len = min(pos_x + len, 320);

    for (int tracer=0; tracer<len; tracer++){
        *location = VGA_COLOR;
        location++;
    }
}

void put_vline(int pos_x, int pos_y, int len, unsigned char vga_color) {
    volatile unsigned char* location = (volatile unsigned char*)0xA0000 + 320 * pos_y + pos_x;

    // Clamp len
    // len = min(pos_y + len, 200);

    for (int tracer=0; tracer<len; tracer++){
        *location = VGA_COLOR;
        location += 320;
    }
}

void putrect(int pos_x, int pos_y, int width, int height, unsigned char vga_color) {
    // Clamp values to screen dimensions
    // width = min(pos_x + width, 320);
    // height = min(pos_y + height, 200);

    // Draw in hlines
    for (int tracer=0; tracer<height; tracer++){
        put_hline(pos_x, pos_y + tracer, width, VGA_COLOR);
    }
}