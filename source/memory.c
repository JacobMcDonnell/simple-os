#include <stdint.h>
#include "memory.h"

void *memcpy(void *dest, const void *src, const size_t n) {
    uint8_t *destB = (void *)dest;
    const uint8_t *srcB = (void *)src;

    for (size_t i = 0; i < n; i++) {
        destB[i] = srcB[i];
    }

    return dest;
}

void *memset(void *s, int c, size_t n) {
    uint8_t *sB = (uint8_t *)s;

    for (size_t i = 0; i < n; i++) {
        sB[i] = (uint8_t)c;
    }

    return s;
}

void *memmove(void *dest, const void *src, const size_t n) {
    uint8_t *db = (uint8_t *)dest;
    const uint8_t *sb = (const uint8_t *)src;

    for (size_t i = n; i > 0; i--) {
        db[i - 1] = sb[i - 1];
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, const size_t n) {
    const uint8_t *s1b = (const uint8_t *)s1;
    const uint8_t *s2b = (const uint8_t *)s2;

    for (size_t i = 0; i < n; i++) {
        if (s1b[i] != s2b[i]) {
            return ((s1b[i] > s2b[i]) ? 1 : -1);
        }
    }

    return 0;
}

