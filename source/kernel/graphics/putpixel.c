#include "putpixel.h"

#include <stdint.h>
#include <envvars.h>

#if defined(RGB8)

// IN BYTES
int ROWSIZE = 320;
int COLSIZE = 200;

inline vga_ptr calc_fb_location(int x, int y) {
    return (volatile unsigned char*)fb + ROWSIZE * y + x;
}

#elif defined(ARGB32)

// IN BYTES
#define ROWSIZE bootboot.fb_scanline
#define COLSIZE bootboot.fb_height

inline vga_ptr calc_fb_location(int x, int y) {
    return ((vga_ptr)(&fb + 4*x + ROWSIZE * y));
}

#endif

void putpixel(int pos_x, int pos_y, pixel_color_t color) {
    *calc_fb_location(pos_x, pos_y) = color;
}

void put_hline(int pos_x, int pos_y, int len, pixel_color_t color) {
    vga_ptr location = calc_fb_location(pos_x, pos_y);

    // Clamp len
    // len = min(pos_x + len, 320);

    for (int tracer=0; tracer<len; tracer++){
        *location = color;
        location++; // pointer addition is weird // this adds by index rather than value 1 like in asm
    }
}

void put_vline(int pos_x, int pos_y, int len, pixel_color_t color) {
    // volatile unsigned char* location = (volatile unsigned char*)fb + 320 * pos_y + pos_x;
    vga_ptr location = calc_fb_location(pos_x, pos_y);
    // Clamp len
    // len = min(pos_y + len, 200);

    for (int tracer=0; tracer<len; tracer++){
        *location = color;
        location += ROWSIZE / 4; // 32 bit pointer increments by 4 bytes
    }
}

void putrect(int pos_x, int pos_y, int width, int height, pixel_color_t color) {
    // Clamp values to screen dimensions
    // width = min(pos_x + width, 320);
    // height = min(pos_y + height, 200);

    // Draw in hlines
    for (int tracer=0; tracer<height; tracer++){
        put_hline(pos_x, pos_y + tracer, width, color);
    }
}