#ifndef MSR_H
#define MSR_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct MSR_Response {
    uint32_t low;
    uint32_t high;
} MSR_Response_t;

MSR_Response_t cpu_read_msr(uint32_t msr);

void cpu_write_msr(uint32_t msr, uint32_t low, uint32_t high);

#ifdef __cplusplus
}
#endif
#endif