#ifndef MEM_H
#define MEM_H
#ifdef __cplusplus
extern "C" {
#endif

#include <envvars.h>
#include <stddef.h>

/**
 * @brief Copies data from dest to src in linear fashion
 * 
 * @param dest Destination pointer
 * @param src Source pointer
 * @param len Number of bytes to copy
 */
void *memcpy(void* dest, const void* src, size_t len);

/**
 * @brief Writes data to destination with a byte
 * 
 * @param dest Destination pointer 
 * @param value Value to be written
 * @param len Number of bytes to set
 */
void *memset(void* dest, int value, size_t len);

/**
 * @brief Moves data from dest to src all at once. Differs from memcpy by storing data into intermediate buffer
 * 
 * @param dest Destination pointer
 * @param src Source pointer
 * @param len Number of bytes to move
 */
void *memmove(void* dest, const void* src, size_t len);

/**
 * @brief Compares memory data
 * 
 * @param s1 First memory section
 * @param s2 Second memory section 
 * @param n Size, in bytes
 * @return int 0 if the memory sections are the same, if not, the first difference
 */
int memcmp(const void *s1, const void *s2, size_t n);

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) :"memory");
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

#ifdef __cplusplus
}
#endif
#endif