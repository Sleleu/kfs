#include <io.h>
#include <kfslib.h>
#include <interrupt.h>
#include <timer.h>
#include <keyboard.h>

void print_requirements(void) {
    terminal_setcolor(VGA_L_CYAN);
	printk("KFS-1 requirements:\n");
	printk("42\n");

	terminal_setcolor(VGA_L_GREEN);
	printk("KFS-2 requirements:\n");
	ptr_t *gdt_addr = (ptr_t *)0x800;
	hexdump(gdt_addr, 64);

	char *gdt_offset = (char *)0x800 + GDT_SIZE;
	printk("GDTR offset: %d\n", *gdt_offset);

	char *begin_gdt = (char *)(0x800 + GDT_SIZE + sizeof(uint16_t));
	printk("GDTR begin address of GDT: %p\n", *(ptr_t *)begin_gdt);

}

void kernel_main(void) {

	idt_install();

	terminal_initialize();
    /* Print header */

	terminal_putheader();
	print_requirements();

	init_timer();
	init_keyboard();

	// uncomment to try division by zero
	// printk("\nTry interrupt:\n");
	// printk("\nResult: %d", 5 / 0);



}
