#ifndef FONTS_H
#define FONTS_H

/*
FONT PROTOCOL (TEMP) DEPRECATED SPEC

Note: when filesystems go online, this spec will change

Raw data for fonts will be declared in a headerfile. It will include this fonts.h headerfile for type declarations.
Each character will be defined as a `const fontchar`. It will then create a font and initialize the const fontchar pointers.
(PENDING) A font registration handler to be implemented
That font headerfile along with this one will be included as the font, an an extern declaration to the fontname will be added. 
This font api can then be used to handle fonts but DRAWING fonts is up to the tty handler
*/

// font chars will be serialized bitmaps. Since we can't store all the data in an int, we will use short[] and jsut have an implementation detail to not read past

typedef struct {
    int fc_width;
    int fc_height;
    short* const data;
} fontchar;

typedef struct {
    int fc_width;
    int fc_height;
    fontchar data[128];
} font;

// TODO: doxygen?
/**
 * @brief Interface to map chars to fontchars without directly accessing the data member
 * @param c ASCII Character to be converted
 * @param fnt Which font to use
 * @return Pointer to the fontchar in a font's array
*/
fontchar* char_to_fontchar(char c, font *fnt);

/**
 * @brief Translates a complete string to a font.
 * @param sbuf A null-terminated string as input
 * @param outbuf A pointer to an array of fontchar pointers. This function will write to the array with the pointers to its chars
 * @param fnt The font to use
 */
void translate_string(char *sbuf, fontchar **outbuf, struct font* fnt);

#endif