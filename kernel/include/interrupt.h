# ifndef KERNEL_INCLUDE_INTERRUPT_H
# define KERNEL_INCLUDE_INTERRUPT_H

/* --------------------------- DEFINES ---------------------------- */
/* flags -> 8 bits for P, DPL, R, GT */
#define INTR_GATE_32B_KERNEL    0x8E  // 10001110
#define TRAP_GATE_32B_KERNEL    0x8F  // 10001111
#define INTR_GATE_32B_USER      0xEE  // 11101110
#define TRAP_GATE_32B_USER      0xEF  // 11101111

/* segment selector -> 16 bits */
#define SEG_KERNEL_CODE         0x08
#define SEG_KERNEL_DATA         0x10

/* PIC */
#define PIC1                    0x20
#define PIC2                    0xA0

#define PIC1_CMD_PORT           PIC1
#define PIC1_DATA_PORT          0x21
#define PIC2_CMD_PORT           PIC2
#define PIC2_DATA_PORT          0xA1

/* ---------------------------------------------------------------- */


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
struct interrupt_registers
{
    uint32_t cr2;                                       /* control register */
    uint32_t ds;                                        /* data segment register */
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;    /* pushed by 'pusha' */
    uint32_t int_no, err_code;                          /* 'push byte #' and err codes do this */
    uint32_t eip, cs, eflags, useresp, ss;              /* pushed by the processor automatically */ 
};

/* ---------------------------------------------------------------- */


/* ------------------------- DECLARATIONS ------------------------- */

/* idt.c */
void idt_install(void);

/* idt_init.asm */
extern void idt_flush(uint32_t);

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

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

/* ---------------------------------------------------------------- */

# endif