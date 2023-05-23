#ifndef STRING_H
#define STRING_H

#include "typedef.h"

// Returns length of null terminated string
size_t strlen(const char* str);

// Returns pointer to the null byte of string
const char* strend(const char* str);

// Finds the first occurence of a char in a null-terminated string
// Returns the pointer to the null byte if not found
const char* findc(const char* src, const char* c);

// Finds the first occurence of a null-terminated string in a null-terminated string
// returns end of string (null byte) if not found
const char* finds(const char* src, const char* s);

/**
 * @brief Compares two strings up to a length.
 * 
 * @param a First string.
 * @param b Second string.
 * @param n The amount of characters to check.
 * @return bool True if they differ.
 */
bool strncmp(char *a, char* b, size_t n);

void reverse(char* s, int len);

void itoa(uint64_t x, char* buffer);

void hex(uint64_t x, char* buffer);

#endif