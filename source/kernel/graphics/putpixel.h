#ifndef PUTPIXEL_H
#define PUTPIXEL_H

#include <envvars.h>

#if defined(RGB8)

typedef unsigned char pixel_color_t;
typedef volatile unsigned char* vga_ptr;

extern void* fb;

enum VGA_COLOR {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

#elif defined(ARGB32)

typedef uint32_t pixel_color_t;
typedef uint32_t* vga_ptr;

enum VGA_COLOR {
    BLACK           = 0x000000,
    BLUE            = 0x0000FF,
    GREEN           = 0x00FF00,
    CYAN            = 0x00FFFF,
    RED             = 0xFF0000,
    MAGENTA         = 0xFF00FF,
    BROWN           = 0x964B00,
    LIGHTGRAY       = 0xD3D3D3,
    DARKGRAY        = 0x5A5A5A,
    LIGHTBLUE       = 0xADD8E6,
    LIGHTGREEN      = 0x90EE90,
    LIGHTCYAN       = 0xE0FFFF,
    LIGHTRED        = 0xFFCCCB,
    LIGHTMAGENTA    = 0xFF80FF,
    YELLOW          = 0xFFFF00,
    WHITE           = 0xFFFFFF
};

#endif

extern inline vga_ptr calc_fb_location(int x, int y);

void putpixel(int pos_x, int pos_y, pixel_color_t color);
void put_hline(int pos_x, int pos_y, int len, pixel_color_t color);
void put_vline(int pos_x, int pos_y, int len, pixel_color_t color);
void putrect(int pos_x, int pos_y, int width, int height, pixel_color_t color);

#endif