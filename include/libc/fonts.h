#ifndef FONTS_H
#define FONTS_H

#include <libc/typedef.h>

// font chars will be serialized bitmaps. Since we can't store all the data in a byte-sized char, we will use int[] and jsut have an implementation detail to not read past
typedef byte* fontchar;

struct font {
    byte fc_width;
    byte fc_height;
    fontchar *data[128];
};

// TODO: doxygen?

extern void _init_spleen_font();
extern struct font spleen_font; // should this be void* ? and then reinterpret later?

/**
 * @brief Interface to map chars to fontchars without directly accessing the data member
 * @param c ASCII Character to be converted
 * @param fnt Which font to use
 * @return Pointer to the fontchar in a font's array
*/
fontchar* ctofc(char c, struct font *fnt);

/**
 * @brief Translates a complete string to a font.
 * @param sbuf A null-terminated string as input
 * @param outbuf A pointer to an array of fontchar pointers. This function will write to the array with the pointers to its chars
 * @param outbuf_len Length of outbuf
 * @param fnt The font to use
 */
void translate_string(char *sbuf, fontchar **outbuf, size_t outbuf_len, struct font* fnt);

#endif