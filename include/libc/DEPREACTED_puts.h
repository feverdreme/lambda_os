#if 0

#ifndef PUTS_H
#define PUTS_H

#include "../libc/typedef.h"

char volatile *const VGA_VIDEO_MEMORY = (char volatile*)0xB8000;
struct {
    int8_t width;
    int8_t height;
} const QEMU_SCREEN_DIM = {80, 25};

int8_t cursor_x = 0, cursor_y = 0;

void puts(const char* str, size_t len) {
    volatile char* video = VGA_VIDEO_MEMORY;

    while (*str) {
        if (cursor_x > QEMU_SCREEN_DIM.width) {
            cursor_x = 0;
            cursor_y++;
        }

        if (*str == '\n'){
            cursor_x = 0;
            cursor_y++;

        } else if (*str == '\t') 
            cursor_x += 4;
        else {
            *(video + (cursor_x + cursor_y * QEMU_SCREEN_DIM.width) * 2) = *str;
            cursor_x++;
        }

        str++;
    }
}

#endif

#endif