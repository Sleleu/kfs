#ifndef KERNEL_INCLUDE_IO_H
#define KERNEL_INCLUDE_IO_H

#include "kfsdef.h"

/* io.c */
void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_putheader(void);
void move_cursor(size_t x, size_t y);

/* outb.asm */
void outb(uint16_t port, uint8_t data);

/* inb.asm */
uint8_t inb(uint16_t port);

/* printk.c */
void printk(const char *format, ...);
void putstr(const char *s);

#endif