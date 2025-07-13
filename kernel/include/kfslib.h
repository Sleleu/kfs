#ifndef KERNEL_INCLUDE_KFSLIB_H
#define KERNEL_INCLUDE_KFSLIB_H

#include <kfsdef.h>

/* strlen.c */
size_t strlen(const char* str);

/* printk.c */
void printk(const char *format, ...);
void putchar(const char c);
void putstr(const char *str);
void hexdump(const void *addr, size_t size);

/* memset.c */
void*   memset(void *b, size_t c, size_t len);

#endif