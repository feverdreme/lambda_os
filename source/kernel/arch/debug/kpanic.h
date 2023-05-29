#ifndef KPANIC_H
#define KPANIC_H
#ifdef __cplusplus
extern "C" {
#endif

#include <graphics/puts.h>
#include <graphics/putpixel.h>

void kpanic(const char* msg);

#ifdef __cplusplus
}
#endif
#endif