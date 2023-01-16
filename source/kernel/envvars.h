#ifndef ENVVARS_H
#define ENVVARS_H

#include <stdint.h>
#include <stdbool.h>

/* -------------------------------------------------------------------------- */
/*                                 OS BITMODE                                 */
/* -------------------------------------------------------------------------- */
#define OS_BITMODE 64

#if OS_BITMODE == 32
#define OS_MAXINT INT32_MAX
#define OS_MAXUINT UINT32_MAX

#elif OS_BITMODE == 64
#define OS_MAXINT INT64_MAX
#define OS_MAXUINT UINT64_MAX

#endif

/* -------------------------------------------------------------------------- */
/*                                DISPLAY MODE                                */
/* -------------------------------------------------------------------------- */
#define ARGB32

/* -------------------------------------------------------------------------- */
/*                                  BOOTBOOT                                  */
/* -------------------------------------------------------------------------- */

#include <bootboot.h>
extern BOOTBOOT bootboot;               // see bootboot.h
extern unsigned char environment[4096]; // configuration, UTF-8 text key=value pairs
extern uint8_t fb;                      // linear framebuffer mapped 
extern void* mmio;

#endif