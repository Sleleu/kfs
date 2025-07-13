#include "../include/kfsdef.h"
#include "../include/interrupt.h"
#include "../include/io.h"

/* flags -> 8 bits for P, DPL, R, GT */
#define INTR_GATE_32B_KERNEL    0x8E  // 10001110
#define TRAP_GATE_32B_KERNEL    0x8F  // 10001111
#define INTR_GATE_32B_USER      0xEE  // 11101110
#define TRAP_GATE_32B_USER      0xEF  // 11101111

/* segment selector -> 16 bits */
#define SEG_KERNEL_CODE         0x08
#define SEG_KERNEL_DATA         0x10


void isrs_install(void)
{
    idt_set_gate(0, (uint32_t)isr0, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(1, (uint32_t)isr1, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(2, (uint32_t)isr2, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(3, (uint32_t)isr3, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(4, (uint32_t)isr4, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(5, (uint32_t)isr5, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(6, (uint32_t)isr6, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(7, (uint32_t)isr7, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(8, (uint32_t)isr8, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(9, (uint32_t)isr9, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(10, (uint32_t)isr10, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(11, (uint32_t)isr11, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(12, (uint32_t)isr12, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(13, (uint32_t)isr13, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(14, (uint32_t)isr14, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(15, (uint32_t)isr15, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(16, (uint32_t)isr16, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(17, (uint32_t)isr17, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(18, (uint32_t)isr18, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(19, (uint32_t)isr19, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(20, (uint32_t)isr20, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(21, (uint32_t)isr21, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(22, (uint32_t)isr22, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(23, (uint32_t)isr23, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(24, (uint32_t)isr24, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(25, (uint32_t)isr25, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(26, (uint32_t)isr26, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(27, (uint32_t)isr27, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(28, (uint32_t)isr28, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(29, (uint32_t)isr29, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(30, (uint32_t)isr30, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(31, (uint32_t)isr31, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
}

char *exception_messages[] =
{
    "Division By Zero",                         // 0
    "Debug",                                    // 1
    "Non Maskable Interrupt",                   // 2
    "Breakpoint Exception",                     // 3
    "Into Detected Overflow Exception",         // 4
    "Out of Bounds Exception",                  // 5
    "Invalid Opcode Exception",                 // 6
    "No Coprocessor Exception",                 // 7
    "Double Fault Exception",                   // 8
    "Coprocessor Segment Overrun Exception",    // 9
    "Bad TSS Exception",                        // 10
    "Segment Not Present Exception",            // 11
    "Stack Fault Exception",                    // 12
    "General Protection Fault Exception",       // 13
    "Page Fault Exception",                     // 14
    "Unknown Interrupt Exception",              // 15
    "Coprocessor Fault Exception",              // 16
    "Alignment Check Exception (486+)",         // 17
    "Machine Check Exception (Pentium/586+)",   // 18
    "Reserved",                                 // 19
    "Reserved",                                 // 20
    "Reserved",                                 // 21
    "Reserved",                                 // 22
    "Reserved",                                 // 23
    "Reserved",                                 // 24
    "Reserved",                                 // 25
    "Reserved",                                 // 26
    "Reserved",                                 // 27
    "Reserved",                                 // 28
    "Reserved",                                 // 29
    "Reserved",                                 // 30
    "Reserved",                                 // 31
};

/* All of our Exception handling Interrupt Service Routines will
*  point to this function. This will tell us what exception has
*  happened! Right now, we simply halt the system by hitting an
*  endless loop. All ISRs disable interrupts while they are being
*  serviced as a 'locking' mechanism to prevent an IRQ from
*  happening and messing up kernel data structures */
void fault_handler(struct regs *r)
{
    /* Get fault from 0 to 31 */
    if (r->int_no < 32)
    {
        /* Display the description for the Exception that occurred. */
        printk("'%s'", exception_messages[r->int_no]);
        printk(" Exception. System Halted!\n");
        for (;;);
    }
}