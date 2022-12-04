#ifndef FONTS_H
#define FONTS_H

#include <libc/typedef.h>

// font chars will be serialized bitmaps. Since we can't store all the data in a byte-sized char, we will use int[] and jsut have an implementation detail to not read past
typedef byte* fontchar;

typedef struct font {
    int fc_width;
    int fc_height;
    fontchar data[128];
} font_t;

// TODO: doxygen?

extern font_t spleen_font; // should this be void* ? and then reinterpret later?
extern void init_spleen_font();

/**
 * @brief Interface to map chars to fontchars without directly accessing the data member
 * @param c ASCII Character to be converted
 * @param fnt Which font to use
 * @return Pointer to the fontchar in memory
*/
fontchar ctofc(char c, font_t *fnt);

#endif