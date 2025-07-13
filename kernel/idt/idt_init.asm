global idt_init
extern idt_pointer

idt_init:
    lidt [idt_pointer]
    ret