#include "kdmsg.h"

#include <graphics/puts.h>

void kdmsg(const char* msg) {
    prints("DEBUG: ");
    prints(msg);
    println();
}