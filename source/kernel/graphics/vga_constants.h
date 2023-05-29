#ifndef VGA_CONSTANTS_H
#define VGA_CONSTANTS_H
#ifdef __cplusplus
extern "C" {
#endif

#include <envvars.h>

#if defined(RGB8)

typedef unsigned char pixel_color_t;

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

#ifdef __cplusplus
}
#endif
#endif