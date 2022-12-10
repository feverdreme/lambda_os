#include <libc/fonts.h>
#include <libc/string.h>

fontchar ctofc(char c, font_t *fnt) {
    return fnt->data[(uint8_t)c];
}

int font_strlen(const char *str, font_t *fnt) {
    return strlen(str) * spleen_font.fc_width + cursor.kerning * (strlen(str) - 1);
}