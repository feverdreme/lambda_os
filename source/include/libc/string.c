#include "typedef.h"

// Returns length of null terminated string
size_t strlen(const char* str) {
    size_t size = 0;

    while (*(str + size) != '\0') size++;
    return size;
}

const char* strend(const char* str) {
    while (*str++ != 0)
        ;
    return str - 1;
}

// Finds the first occurence of a char in a null-terminated string
// Returns the pointer to the null byte if not found
const char* findc(const char* src, const char* c) {
    while (*src != *c && *src != 0) src++;

    return src;
}

// Finds the first occurence of a null-terminated string in a null-terminated
// string returns end of string (null byte) if not found
const char* finds(const char* src, const char* s) {
    // Increment on src until we find the first matching character
    // if found, then iterate to check the two strings are alike
    // if alike, return the pointer to the first char found
    // if not alike, keep searching
    // if not found, return pointer to the end

    while (1) {
        if (*src == 0) return src;
        if (*src != *s) {
            src++;
            continue;
        }

        src++;
        s++;

        for (int i = 1;; i++) {
            // Reached the end of s find
            if (*s == 0) return src - i;
            if (*src != *s) {
                s -= i;
                break;
            }
            src++;
            s++;
        }
    }
}

bool strncmp(char *a, char* b, size_t n) {
    for (size_t i=0; i<n; i++) {
        if (*a != *b) return true;
        a++;
        b++;
    }

    return false;
}

void reverse(char* begin, char* end)
{
    while (begin < end) {
        char temp = *end;
        *end = *begin;
        *begin = temp;

        begin++;
        end--;
    }
}

void itoa(uint64_t x, char* buf) {
    static const char* lookup = "0123456789";

    if (x == 0) {
        buf[0] = '0';
        return;
    }

    if (x < 0) {
        *buf = '-';
        x *= -1;
        buf++;
    }

    char* start = buf;
    while (x != 0) {
        *buf = lookup[x % 10];
        x /= 10;
        buf++;
    }

    *buf = '\0';

    reverse(start, buf - 1);
}

void hex(uint64_t x, char* buffer) {
    static const char* lookup = "0123456789abcdef";

    if (x == 0) {
        buffer[0] = '0';
        return;
    }

    if (x < 0) {
        *buffer = '-';
        x *= -1;
        buffer++;
    }

    char* start = buffer;
    while (x != 0) {
        *buffer = lookup[x % 16];
        x /= 16;
        buffer++;
    }

    *buffer = '\0';

    reverse(start, buffer - 1);    
}