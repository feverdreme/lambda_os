#ifndef KEYBOARD_H
#define KEYBOARD_H
#ifdef __cplusplus
extern "C" {
#endif

#include <arch/idt/isr.h>

/**
 * @brief The interrupt handler for the keyboard
 * 
 */
__attribute__((interrupt))
void keyboard_handler(interrupt_frame_t* frame);

/**
 * @brief Registers the keyboard.
 * 
 */
void isr_keyboard_register();

#ifdef __cplusplus
}
#endif
#endif