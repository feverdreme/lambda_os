#include <libc/fonts.h>
#include <libc/string.h>

fontchar* ctofc(char c, font_t *fnt) {
    // c needs to be converted to its ascii code to be indexed
    // this doens't check whether it's printable
    
    return &fnt->data[(ascii_code_t)c * 8];
}

int font_strlen(const char *str, font_t *fnt, int kerning) {
    return strlen(str) * fnt->fc_width + kerning * (strlen(str) - 1);
}