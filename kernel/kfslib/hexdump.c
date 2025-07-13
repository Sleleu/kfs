#include <kfsdef.h>
#include <kfslib.h>

static void puthex_byte(uint8_t b) {
	const char *digits = "0123456789ABCDEF";

	putchar(digits[(b >> 4) & 0xF]);
	putchar(digits[b & 0xF]);
}

static void puthex_padd(uint32_t value) {
	char hex[9];
	const char *digits = "0123456789ABCDEF";

	for (int i = 7; i >= 0; i--) {
		hex[i] = digits[value & 0xF];
		value >>= 4;
	}
	hex[8] = '\0';
	putstr(hex);
}

void hexdump(const void *addr, size_t size) {
	const uint8_t *ptr = (const uint8_t *)addr;
	for (size_t i = 0; i < size; i += 16) {
		// print address
		puthex_padd((ptr_t)(ptr + i));
		putstr("  ");

		// print hex
		for (size_t j = 0; j < 16; j++) {
			if (i + j < size) {
				puthex_byte(ptr[i + j]);
				putchar(' ');
			}
            else
				putstr("   "); // align
			if (j == 7)
				putchar(' '); // space between 2 bytes
		}

		putchar(' ');

		// print ascii value
		for (size_t j = 0; j < 16 && (i + j) < size; j++) {
			char c = ptr[i + j];
			if (c >= 32 && c <= 126)
				putchar(c);
			else
				putchar('.');
		}
		putchar('\n');
	}
}
