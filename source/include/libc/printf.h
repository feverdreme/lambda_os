#ifndef PRINTF_H
#define PRINTF_H

#include <stdarg.h>

// Supports %d ONLY
void printf(const char* fmt, ...){
    va_list valist;
    va_start(valist, fmt);

    
}

#endif