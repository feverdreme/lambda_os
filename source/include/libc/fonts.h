#ifndef FONTS_H
#define FONTS_H

#include <libc/typedef.h>

#define NONPRINTABLE_FONTCHAR 0

// font chars will be serialized bitmaps. Since we can't store all the data in a byte-sized char, we will use int[] and jsut have an implementation detail to not read past
typedef byte* fontchar;

typedef struct font {
    uint32_t fc_width;
    uint32_t fc_height;
    bool is_printable[128];
    fontchar data[128];
} font_t;

extern font_t spleen_font; // should this be void* ? and then reinterpret later?

/**
 * @brief Interface to map chars to fontchars without directly accessing the data member
 * @param c ASCII Character to be converted
 * @param fnt Which font to use
 * @return Pointer to the fontchar in memory
*/
fontchar ctofc(char c, font_t *fnt);

/**
 * @brief Calculates the pixel length of a string in a font
 * 
 * @param str The string data
 * @param fnt The font the string will be put in
 * @param kerning The kerning that would be used
 * @return The length in pixels
 */
int font_strlen(const char *str, font_t *fnt, int kerning);

#endif