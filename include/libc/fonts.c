#include <libc/fonts.h>

fontchar ctofc(char c, font_t *fnt) {
    return fnt->data[(uint8_t)c];
}