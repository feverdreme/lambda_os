#ifndef PUTPIXEL_H
#define PUTPIXEL_H

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

void putpixel(int pos_x, int pos_y, unsigned char vga_color);
void put_hline(int pos_x, int pos_y, int len, unsigned char vga_color);
void put_vline(int pos_x, int pos_y, int len, unsigned char vga_color);
void putrect(int pos_x, int pos_y, int width, int height, unsigned char vga_color);

#endif