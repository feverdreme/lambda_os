#ifndef CPUID_QUERY_H
#define CPUID_QUERY_H

static inline int get_MAXPHYADDR() {
    int cpuid_code = 0x80000008; // EAX code for CPUID call

    int eax, unused;
    __get_cpuid(cpuid_code, &eax, &unused, &unused, &unused);

    return eax & (0xff); // EAX[7:0]
}

extern int MAXPHYADDR;

#endif