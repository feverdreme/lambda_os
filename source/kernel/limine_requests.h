#ifndef LIMINE_REQUESTS_H
#define LIMINE_REQUESTS_H

#include <limine.h>

extern volatile struct limine_framebuffer_request framebuffer_request;

extern volatile struct limine_kernel_address_request kernel_address_request;

extern volatile struct limine_hhdm_request hhdm_request;

#endif