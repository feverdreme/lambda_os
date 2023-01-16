#include "kpanic.h"

void kpanic(const char* msg){
    // clear first line
    putrect(0, 0, 320, 8, 0x00DDDDDD);

    cursor.x = 0;
    cursor.y = 0;
    cursor.kerning = 1;
    cursor.color = 0x0000FF00;

    prints("KERNEL PANIC: ");
    prints(msg);

    asm("hlt");
}