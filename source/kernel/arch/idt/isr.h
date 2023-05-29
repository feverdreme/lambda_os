#ifndef ISR_H
#define ISR_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct interrupt_frame {
    uint64_t ip;
    uint64_t cs;
    uint64_t flags;
    uint64_t sp;
    uint64_t ss;
} interrupt_frame_t;

#ifdef __cplusplus
}
#endif
#endif