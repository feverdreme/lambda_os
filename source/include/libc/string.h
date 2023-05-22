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

void reverse(char* s, int len);

void itoa(uint64_t x, char* buffer);

void hex(uint64_t x, char* buffer);

#endif