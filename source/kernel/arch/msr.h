#ifndef MSR_H
#define MSR_H

#include <stdint.h>

typedef struct MSR_Response {
    uint32_t low;
    uint32_t high;
} MSR_Response_t;

MSR_Response_t cpu_read_msr(uint32_t msr);

MSR_Response_t cpu_write_msr(uint32_t msr, uint32_t low, uint32_t high);

#endif