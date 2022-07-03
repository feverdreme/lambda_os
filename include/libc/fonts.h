#ifndef FONTS_H
#define FONTS_H

// idea: use csv/pillow python script to generate bitmap font
// TODO: establish a naming convention

/*
FONT PROTOCOL (TEMP)

Note: when filesystems go online, this spec will change

Raw data for fonts will be declared in a headerfile. It will include this fonts.h headerfile for type declarations.
Each character will be defined as a `const fontchar`. It will then create a font and initialize the const fontchar pointers.
(PENDING) A font registration handler to be implemented
That font headerfile along with this one will be included as the font, an an extern declaration to the fontname will be added. 
This font api can then be used to handle fonts but DRAWING fonts is up to the tty handler
*/

typedef char fontchar[8][8];

// Currently only supports 0x21 to 0x5A
struct font {
    // int support_low;
    // int support_high;
    const fontchar *data[0x5A - 0x21]; 
    int kerning;
};

void register_char(char c, const fontchar *fc, struct font* f);

// Interfacing with strings
const fontchar* char_to_fontchar(char c, struct font *fnt);
void translate_string(char *sbuf, fontchar **outbuf, struct font* fnt);

#endif