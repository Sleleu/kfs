#ifndef KERNEL_INCLUDE_KFSDEF_H
#define KERNEL_INCLUDE_KFSDEF_H

#define VGA_MEMORY 0xB8000   /* video memory begins here. */
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define GDT_SIZE  56

/* TYPEDEF */
typedef unsigned char uint8_t;
typedef unsigned char u8_t;

typedef unsigned short uint16_t;
typedef unsigned short u16_t;

typedef unsigned int uint32_t;
typedef unsigned int u32_t;

typedef unsigned long size_t;
typedef unsigned long ptr_t;

typedef unsigned long long uint64_t;
typedef unsigned long long u64_t;

/* Hardware text mode color constants. */
enum vga_color {
	VGA_BLACK = 0,
	VGA_BLUE = 1,
	VGA_GREEN = 2,
	VGA_CYAN = 3,
	VGA_RED = 4,
	VGA_MAGENTA = 5,
	VGA_BROWN = 6,
	VGA_L_GREY = 7,
	VGA_D_GREY = 8,
	VGA_L_BLUE = 9,
	VGA_L_GREEN = 10,
	VGA_L_CYAN = 11,
	VGA_L_RED = 12,
	VGA_L_MAGENTA = 13,
	VGA_L_BROWN = 14,
	VGA_WHITE = 15,
};

#endif