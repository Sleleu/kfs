#include <kfsdef.h>
#include <kfslib.h>
#include <interrupt.h>

/* Declare an IDT of 256 entries and IDT pointer*/
struct idt_entry idt[256];
struct idt_ptr idt_pointer;

/* set an entry in the IDT */
void idt_set_gate(uint8_t num, uint32_t base, uint16_t seg_selector, uint8_t flags)
{
   
   /* Write base address */
   idt[num].base_hi = (base >> 16) & 0xFFFF;
   idt[num].base_lo = base & 0xFFFF;

   idt[num].seg_selector = seg_selector;
   /* Should be useless with memset but we secure */
   idt[num].reserved = 0b00000000;
   idt[num].flags = flags;

}

/* Installs the IDT */
void idt_install(void)
{
    /* Sets the special IDT pointer up */
    idt_pointer.limit = (sizeof (struct idt_entry) * 256) - 1;
    idt_pointer.base = (uint32_t)&idt;

    /* init IDT with zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    /* set idt gate from 0 to 31 */
    isrs_install();

    /* call idt_init label in idt_init.asm */
    idt_init();

}