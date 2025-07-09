#include "../include/io.h"
#include "../include/kfslib.h"

/* VARIABLES */
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;
unsigned int vga_index;


static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
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

void terminal_scroll(void) {
	
	/* We drop one line */
	size_t screen_size = VGA_WIDTH * VGA_HEIGHT;

	/* Shift line row N on row N - 1  */
	for (size_t i = 0, j = i + VGA_WIDTH; j < screen_size; i++, j++)
		terminal_buffer[i] = terminal_buffer[j];
	
	/* Draw blank line down */
	for (size_t i = screen_size - VGA_WIDTH; i < screen_size; i++)
		terminal_buffer[i] = vga_entry(' ', terminal_color);

}

void terminal_putnewline(void) {
    terminal_row++;
    terminal_column = 0;

    if (terminal_row >= VGA_HEIGHT) {
        terminal_scroll();
        terminal_row = VGA_HEIGHT - 1;
    }
}

void terminal_putchar(char c) {
    /* Handle newline */
    if (c == '\n')
        terminal_putnewline();
    else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            terminal_putnewline();
        }
    }
    move_cursor(terminal_column, terminal_row);
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

#define FB_CMD_PORT     0x3D4
#define FB_DATA_PORT    0x3D5

#define CURSOR_HIGH_BYTE_CMD    0xE
#define CURSOR_LOW_BYTE_CMD     0xF

void move_cursor(size_t x, size_t y) {
    uint16_t pos = (y * VGA_WIDTH) + x;
    outb(FB_CMD_PORT, CURSOR_HIGH_BYTE_CMD);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));

    outb(FB_CMD_PORT, CURSOR_LOW_BYTE_CMD);
    outb(FB_DATA_PORT, pos & 0x00FF);
}
