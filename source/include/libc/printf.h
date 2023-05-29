#ifndef PRINTF_H
#define PRINTF_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

// Supports %d ONLY
void printf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif
#endif