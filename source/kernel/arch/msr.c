#include "msr.h"

MSR_Response_t cpu_read_msr(uint32_t msr) {
    MSR_Response_t ret;

    __asm__ volatile ("rdmsr" : "=a"(ret.low), "=d"(ret.high) : "c"(msr));
    return ret;
}

void cpu_write_msr(uint32_t msr, uint32_t low, uint32_t high) {
    __asm__ volatile ("wrmsr" : : "a"(low), "d"(high), "c"(msr));
}