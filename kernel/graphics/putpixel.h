#ifndef PUTPIXEL_H
#define PUTPIXEL_H

void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR);
void put_hline(int pos_x, int pos_y, int len, unsigned char VGA_COLOR);
void put_vline(int pos_x, int pos_y, int len, unsigned char VGA_COLOR);
void putrect(int pos_x, int pos_y, int width, int height, unsigned char VGA_COLOR);

#endif