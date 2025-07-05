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
    terminal_row++;
    terminal_column = 0;
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

void terminal_putchar(char c) {
    /* Handle newline */
    if (c == '\n') {
        terminal_putnewline();
		if (terminal_row == VGA_HEIGHT)
			terminal_scroll();
        return;
    }

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		terminal_putnewline();
		if (terminal_row == VGA_HEIGHT)
			terminal_scroll();
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
	//terminal_writestring("42");

	//char *big_buffer = "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2An3An4An5An6An7An8An9Ao0Ao1Ao2Ao3Ao4Ao5Ao6Ao7Ao8Ao9Ap0Ap1Ap2Ap3Ap4Ap5Ap6Ap7Ap8Ap9Aq0Aq1Aq2Aq3Aq4Aq5Aq6Aq7Aq8Aq9Ar0Ar1Ar2Ar3Ar4Ar5Ar6Ar7Ar8Ar9As0As1As2As3As4As5As6As7As8As9At0At1At2At3At4At5At6At7At8At9Au0Au1Au2Au3Au4Au5Au6Au7Au8Au9Av0Av1Av2Av3Av4Av5Av6Av7Av8Av9Aw0Aw1Aw2Aw3Aw4Aw5Aw6Aw7Aw8Aw9Ax0Ax1Ax2Ax3Ax4Ax5Ax6Ax7Ax8Ax9Ay0Ay1Ay2Ay3Ay4Ay5Ay6Ay7Ay8Ay9Az0Az1Az2Az3Az4Az5Az6Az7Az8Az9Ba0Ba1Ba2Ba3Ba4Ba5Ba";
	//terminal_writestring(big_buffer);

}
