#include "kpanic.h"
#include "../../graphics/puts.h"
#include "../../graphics/putpixel.h"


void kpanic(const char* msg){
    // clear first line
    putrect(0, 0, 320, 8, LIGHTGRAY);

    cursor.x = 0;
    cursor.y = 0;
    cursor.kerning = 1;
    cursor.color = GREEN;

    prints("KERNEL PANIC: ");
    prints(msg);

    asm("hlt");
}