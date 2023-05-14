#include "fb.h"

#include <envvars.h>
#include <arch/debug/kpanic.h>
#include <limine_requests.h>

struct limine_framebuffer *framebuffer;

uint64_t FB_PITCH;
uint64_t FB_WIDTH;
uint64_t FB_HEIGHT;
uint16_t FB_BPP;

void initialize_fb() {
    // Sanity check
    if (framebuffer_request.response == NULL ||
        framebuffer_request.response->framebuffer_count < 1) {
        kpanic("INVALID FRAMEBUFFER INFO");
    }

    framebuffer = framebuffer_request.response->framebuffers[0];

    FB_PITCH = framebuffer->pitch;
    FB_WIDTH = framebuffer->width;
    FB_HEIGHT = framebuffer->height;
    FB_BPP = framebuffer->bpp;
}

vga_ptr calc_fb_location(int x, int y) {
    vga_ptr fb_ptr = framebuffer->address;
    return &fb_ptr[FB_WIDTH * y + x];
}