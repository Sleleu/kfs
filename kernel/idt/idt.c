#include "../include/kfsdef.h"
#include "../include/kfslib.h"
#include "../include/io.h"

/* flags -> 8 bits for P, DPL, R, GT */
#define INT_GATE_32B_KERNEL     = 0b10001110
#define TRAP_GATE_32B_KERNEL    = 0b10001111
#define INT_GATE_32B_USER       = 0b11101110
#define TRAP_GATE_32B_USER      = 0b11101111


/* declaration of label in 'idt_init.asm' */
extern void idt_init();

/* Defines an IDT entry */
struct idt_entry
{
    uint16_t base_lo;       /* Low bits of base address*/
    uint16_t seg_selector;  /* Kernel segment here */
    uint8_t reserved;       /* always set to 0 */
    uint8_t flags;          /* Set using the above table! */
    uint16_t base_hi;       /* High bits of base address*/
} __attribute__((packed));

/* Defines an IDT pointer struct, used in idt_init.asm to load idt*/
struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

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


    /* call idt_init label in idt_init.asm */
    idt_init();

}