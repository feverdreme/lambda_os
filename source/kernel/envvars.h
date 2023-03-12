#ifndef ENVVARS_H
#define ENVVARS_H

#include <stdint.h>
#include <stdbool.h>

#define NULL ((void *)0)

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
// extern void* mmio;

/* -------------------------------------------------------------------------- */
/*                             INTERNAL PIXEL DEFS                            */
/* -------------------------------------------------------------------------- */

#define INTERNAL_WIDTH (320 * 2)
#define INTERNAL_HEIGHT (200 * 2)

/* -------------------------------------------------------------------------- */
/*                              HELPFUL CONSTANTS                             */
/* -------------------------------------------------------------------------- */

typedef enum SUCCESS_STATUS {
    SUCCESS = 0,
    FAILURE = 1
} SUCCESS_STATUS_t;

typedef char** GENERIC_PTR_ARRAY;

#endif