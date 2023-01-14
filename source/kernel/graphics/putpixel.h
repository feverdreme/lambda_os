#ifndef PUTPIXEL_H
#define PUTPIXEL_H

#include <envvars.h>

#if defined(RGB8)

typedef unsigned char pixel_color_t;
typedef volatile unsigned char* vga_ptr;

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

extern void* fb;

#elif defined(ARGB32)

#include <stdint.h>
#include <stdbool.h>
#include <bootboot.h>

typedef uint32_t pixel_color_t;
typedef uint32_t* vga_ptr;

extern BOOTBOOT bootboot;               // see bootboot.h
extern unsigned char environment[4096]; // configuration, UTF-8 text key=value pairs
extern uint8_t fb;                      // linear framebuffer mapped 

#endif

extern inline vga_ptr calc_fb_location(int x, int y);

void putpixel(int pos_x, int pos_y, pixel_color_t color);
void put_hline(int pos_x, int pos_y, int len, pixel_color_t color);
void put_vline(int pos_x, int pos_y, int len, pixel_color_t color);
void putrect(int pos_x, int pos_y, int width, int height, pixel_color_t color);

#endif