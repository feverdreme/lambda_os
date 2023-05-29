#ifndef ENVVARS_H
#define ENVVARS_H
#ifdef __cplusplus
extern "C" {
#endif

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
/*                              HELPFUL CONSTANTS                             */
/* -------------------------------------------------------------------------- */

typedef enum SUCCESS_STATUS {
    SUCCESS = 0,
    FAILURE = 1
} SUCCESS_STATUS_t;

typedef char** GENERIC_PTR_ARRAY;

/* -------------------------------------------------------------------------- */
/*                                   PAGING                                   */
/* -------------------------------------------------------------------------- */

#define IA32E_PAGING

#ifdef __cplusplus
}
#endif
#endif