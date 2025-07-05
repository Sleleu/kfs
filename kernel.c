#define VGA_MEMORY 0xB8000   /* video memory begins here. */
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

/* VGA provides support for 16 colors */
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define L_GREY 7
#define D_GREY 8
#define L_BLUE 9
#define L_GREEN 10
#define L_CYAN 11
#define L_RED 12
#define L_MAGENTA 13
#define YELLOW 14
#define WHITE 15

/* TYPEDEF */
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long size_t;

/* VARIABLES */
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;
unsigned int vga_index;

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

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_L_GREY, VGA_BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putnewline(void) {
    terminal_row ++;
    terminal_column = 0;
}

void terminal_putchar(char c) {
    /* Handle newline */
    if (c == '\n') {
        terminal_putnewline();
        return;
    }

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

void terminal_putheader(void) {

    char *header_42 =
    " ***************************************************************************** \n"
    " *                                                                           * \n"
    " *            .--._.--.                                                      * \n"
    " *           ( O     O )                                 :::      ::::::::   * \n"
    " *           /   . .   \\                              :+:      :+:    :+:    * \n"
    " *          .`._______.'.                            +:+ +:+         +:+     * \n"
    " *         /(           )\\                         +#+  +:+       +#+        * \n"
    " *       _/  \\  \\   /  /  \\_                     +#+#+#+#+#+   +#+           * \n"
    " *    .~   `  \\  \\ /  /  '   ~.                       #+#    #+#             * \n"
    " *   {    -.   \\  V  /   .-    }                     ###   ########          * \n"
    " * _ _`.    \\  |  |  |  /    .'_                                             * \n"
    " * >_       _} |  |  | {_       _<                                           * \n"
    " *  /. - ~ ,_-'  .^.  `-_, ~ - .\\                                            * \n"
    " *          '-'|/   \\|`-`                                                    * \n"
    " ***************************************************************************** \n";

    uint8_t current_row_color = 9;
    terminal_setcolor((++current_row_color));
    
    for (size_t idx = 0; header_42[idx]; idx++) {
        terminal_putchar(header_42[idx]);
        if (header_42[idx] == '\n') {
            terminal_setcolor((current_row_color++ % 6 + 10));
        }
    }
}



void kernel_main(void) {

	terminal_initialize();

    /* Print header */
    terminal_putheader();

    terminal_setcolor(0b00000010);
	terminal_writestring("42");
}
