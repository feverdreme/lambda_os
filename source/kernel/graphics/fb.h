#ifndef FB_H
#define FB_H

#include <stdint.h>

typedef uint32_t* vga_ptr;

extern struct limine_framebuffer *framebuffer;

extern uint64_t FB_PITCH;
extern uint64_t FB_WIDTH;
extern uint64_t FB_HEIGHT;
extern uint16_t FB_BPP;

void initialize_fb();

vga_ptr calc_fb_location(int x, int y);

#endif