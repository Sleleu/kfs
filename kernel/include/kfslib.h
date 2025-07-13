#ifndef KFSLIB_H
#define KFSLIB_H

#include "kfsdef.h"

/* strlen.c */
size_t strlen(const char* str);

/* printk.c */
void printk(const char *format, ...);

/* memset.c */
void*   memset(void *b, size_t c, size_t len);

#endif