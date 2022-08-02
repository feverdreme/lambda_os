#if 1

#ifndef PUTS_H
#define PUTS_H

#include "../libc/typedef.h"
#include <libc/string.h>

char volatile* const VGA_VIDEO_MEMORY = (char volatile*)0xB8000;
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

        if (*str == '\n') {
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

char* itoa(int num, char* str, int base) {
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0) {
        str[i] = '0';
        str[i+1] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // If number is negative, append '-'
    if (isNegative) str[i++] = '-';

    str[i] = '\0';  // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

#endif

#endif