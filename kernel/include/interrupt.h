# ifndef KERNEL_INCLUDE_INTERRUPT_H
# define KERNEL_INCLUDE_INTERRUPT_H

/* -------------------------- STRUCTURES -------------------------- */

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

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    uint32_t gs, fs, es, ds;                            /* pushed the segs last */
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;    /* pushed by 'pusha' */
    uint32_t int_no, err_code;                          /* 'push byte #' and ecodes do this */
    uint32_t eip, cs, eflags, useresp, ss;              /* pushed by the processor automatically */ 
};

/* ---------------------------------------------------------------- */



/* ------------------------- DECLARATIONS ------------------------- */

/* idt.c */
void idt_install(void);
void idt_set_gate(uint8_t num, uint32_t base, uint16_t seg_selector, uint8_t flags);

/* isrs.c */
void isrs_install(void);

/* idt_init.asm */
extern void idt_init();

/* isr.asm */
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

/* ---------------------------------------------------------------- */

# endif