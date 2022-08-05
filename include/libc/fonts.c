#include <libc/fonts.h>

fontchar ctofc(char c, struct font *fnt) {
    return fnt->data[(uint8_t)c];
}