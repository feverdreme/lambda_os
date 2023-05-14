#ifndef PUTPIXEL_H
#define PUTPIXEL_H

#include <envvars.h>
#include <graphics/vga_constants.h>

void putpixel(int pos_x, int pos_y, pixel_color_t color);
void put_hline(int pos_x, int pos_y, int len, pixel_color_t color);
void put_vline(int pos_x, int pos_y, int len, pixel_color_t color);
void putrect(int pos_x, int pos_y, int width, int height, pixel_color_t color);

#endif