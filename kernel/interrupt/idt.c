#include <kfsdef.h>
#include <kfslib.h>
#include <interrupt.h>
#include <io.h>

/* Declare an IDT of 256 entries and IDT pointer*/
struct idt_entry idt[256];
struct idt_ptr idt_pointer;

/* Exception messages */
const char *exception_messages[] =
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

/* set an entry in the IDT */
void idt_set_gate(uint8_t num, uint32_t base, uint16_t seg_selector, uint8_t flags)
{
   
   /* Write base address */
   idt[num].base_hi = (base >> 16) & 0xFFFF;
   idt[num].base_lo = base & 0xFFFF;

   idt[num].seg_selector = seg_selector;
   /* Should be useless with memset but we secure */
   idt[num].reserved = 0b00000000;
   idt[num].flags = flags | 0x60;

}

void isr_handler(struct interrupt_registers *regs) {
    if (regs->int_no < 32) {
        printk("'%s'", exception_messages[regs->int_no]);
        printk("\nException! System Halted\n");
        for(;;);
    }
}

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

    idt_set_gate(32, (uint32_t)irq0, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(33, (uint32_t)irq1, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(34, (uint32_t)irq2, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(35, (uint32_t)irq3, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(36, (uint32_t)irq4, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(37, (uint32_t)irq5, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(38, (uint32_t)irq6, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(39, (uint32_t)irq7, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(40, (uint32_t)irq8, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(41, (uint32_t)irq9, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(42, (uint32_t)irq10, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(43, (uint32_t)irq11, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(44, (uint32_t)irq12, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(45, (uint32_t)irq13, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(46, (uint32_t)irq14, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
    idt_set_gate(47, (uint32_t)irq15, SEG_KERNEL_CODE, INTR_GATE_32B_KERNEL);
}

void pic_remap(void) {
    outb(PIC1_CMD_PORT, 0x11);
    outb(PIC2_CMD_PORT, 0x11);

    outb(PIC1_DATA_PORT, 0x20);
    outb(PIC2_DATA_PORT, 0x28);

    outb(PIC1_DATA_PORT, 0x04);
    outb(PIC2_DATA_PORT, 0x02);

    outb(PIC1_DATA_PORT, 0x01);
    outb(PIC2_DATA_PORT, 0x01);

    outb(PIC1_DATA_PORT, 0x00);
    outb(PIC2_DATA_PORT, 0x00);
}


void *irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void irq_install_handler(int irq, void (*handler)(struct interrupt_registers *regs)) {
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq) {
    irq_routines[irq] = 0;
}

void irq_handler(struct interrupt_registers *regs) {
    void (*handler)(struct interrupt_registers *regs);

    /* interrupt number start at 32 */
    handler = irq_routines[regs->int_no - 32];

    if (handler) {
        handler(regs);
    }
    if (regs->int_no >= 40) {
        outb(PIC2_CMD_PORT, 0x20);
    }

    outb(PIC1_CMD_PORT, 0x20);
}


/* Installs the IDT */
void idt_install(void)
{
    /* Sets the special IDT pointer up */
    idt_pointer.limit = sizeof (struct idt_entry) * 256 - 1;
    idt_pointer.base = (uint32_t)&idt;

    /* init IDT with zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    pic_remap();

    /* set idt gate from 0 to 47 */
    isrs_install();

    /* call idt_flush label in idt_init.asm */
    idt_flush((uint32_t)&idt_pointer);

}