#ifndef ENVVARS_H
#define ENVVARS_H

#define OS_BITMODE 32

#if OS_BITMODE == 32
#define OS_MAXINT INT32_MAX
#define OS_MAXUINT UINT32_MAX

#elif OS_BITMODE == 64
#define OS_MAXINT INT64_MAX
#define OS_MAXUINT UINT64_MAX

#endif

#endif