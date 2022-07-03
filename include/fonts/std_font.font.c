#include <libc/fonts.h>

struct font std_font;

const fontchar A = {
    "########", 
    "#      #", 
    "#      #", 
    "########",
    "#      #", 
    "#      #", 
    "#      #", 
    "#      #",
};

std_font.data[1] = &A;

const fontchar B = {
    "####### ", 
    "#      #", 
    "#      #", 
    "####### ",
    "#      #", 
    "#      #", 
    "#      #", 
    "####### ",
};

const fontchar C = {
    "########", 
    "#       ", 
    "#       ", 
    "#       ",
    "#       ", 
    "#       ", 
    "#       ", 
    "########",
};

const fontchar D = {
    "######  ", 
    "#     # ", 
    "#      #", 
    "#      #",
    "#      #", 
    "#      #", 
    "#     # ", 
    "######  ",
};