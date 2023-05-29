#ifndef CPUID_QUERY_H
#define CPUID_QUERY_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

static inline int get_MAXPHYADDR() {
    int cpuid_code = 0x80000008; // EAX code for CPUID call

    int eax, unused;
    __get_cpuid(cpuid_code, &eax, &unused, &unused, &unused);

    return eax & (0xff); // EAX[7:0]
}

extern int MAXPHYADDR;

static inline bool supports_1gb_pages() {
    int cpuid_code = 0x80000001;

    int edx, unused;
    __get_cpuid(cpuid_code, &unused, &unused, &unused, &edx);

    return edx & (1<<26);
}

#ifdef __cplusplus
}
#endif
#endif