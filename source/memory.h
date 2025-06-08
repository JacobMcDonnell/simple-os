#ifndef MEMORY_H_
#define MEMORY_H_

#include <stddef.h>

void *memcpy(void *dest, const void *src, const size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, const size_t n);
int memcmp(const void *s1, const void *s2, const size_t n);

#endif  // MEMORY_H_

