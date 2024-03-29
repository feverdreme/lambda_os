#include "kpanic.h"

#include <envvars.h>
#include <graphics/fb.h>

void kpanic(const char* msg){
    // clear first line
    putrect(0, 0, FB_WIDTH, 8, 0x00DDDDDD);

    cursor.x = 0;
    cursor.y = 0;
    cursor.kerning = 1;
    cursor.color = 0x0000FF00;

    prints("KERNEL PANIC: ");
    prints(msg);

    asm("hlt");
}