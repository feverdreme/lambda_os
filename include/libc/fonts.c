#include <libc/fonts.h>

fontchar* ctofc(char c, struct font *fnt) {
    if (0 <= c) return fnt->data[(int)c];
    else return 0;
}

void translate_string(char *sbuf, fontchar **outbuf, size_t outbuf_len, struct font* fnt) {
    // is it an antipattern to use outbuf as the incremetned pointer?
    struct fontchar** out_i = outbuf;

    for (char *s_i = sbuf; *s_i != '\0'; s_i++) {
        if (out_i - outbuf + 1 > outbuf_len) break;
        if (ctofc(*s_i, fnt) == 0) continue;
        
        *out_i = ctofc(*s_i, fnt);
        out_i++;
    }
}