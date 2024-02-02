#include "str.h"

// similar to strcpy in C
void strcpy(char* dest, char* src) {
    int idx = 0;
    while (*src != '\0') {
        dest[idx] = *src;
        ++src;
        ++idx;
    }
    dest[idx] = '\0';
}

// strcmp will return 1 if bot strings are equal and 0 if not
int strcmp(char* str1, char* str2) {
    while (*str1 != '\0') {
        if (*str1 != *str2) 
            return 0;
        ++str1;
        ++str2;
    }

    if (str2 != '\0')
        return 0;

    return 1;
}
