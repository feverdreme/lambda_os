#ifndef MEM_H
#define MEM_H

/**
 * @brief Copies data from dest to src in linear fashion
 * 
 * @param dest Destination pointer
 * @param src Source pointer
 * @param len Number of bytes to copy
 */
void memcpy(void* dest, void* src, int len);

/**
 * @brief Writes data to destination with a byte
 * 
 * @param dest Destination pointer 
 * @param value Value to be written
 * @param len Number of bytes to set
 */
void memset(void* dest, char value, int len);

/**
 * @brief Moves data from dest to src all at once. Differs from memcpy by storing data into intermediate buffer
 * 
 * @param dest Destination pointer
 * @param src Source pointer
 * @param len Number of bytes to move
 */
void memmove(void* dest, void* src, int len);

#endif