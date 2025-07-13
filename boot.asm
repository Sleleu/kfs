[bits 32]

; ===== Define constants =====

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -(MAGIC_NUMBER + FLAGS)
KERNEL_STACK_SIZE equ 8192

global start

; ===== declare extern functions =====

extern gdt_init             ; function defined in gdt.asm
extern idt_install          ; function defined in idt.c
extern kernel_main          ; kernel_main function defined in C file


; ===== Multiboot section =====

section .multiboot          ; Multiboot specification
    dd MAGIC_NUMBER         ; Magic number '1 BAD BOOT'
    dd FLAGS                ; Flag
    dd CHECKSUM             ; Checksum


; ===== Text section =====

section .text               ; Section for executable instructions

start:
    cli                     ; Block interrupts, clear the IF flag in the EFLAGS register
    mov esp, stack_space    ; Set stack pointer, moves the empty stack_space function into de Stack Pointer
    call gdt_init           ; install GDT, enter in protected mode
    call idt_install        ; load IDT
    call kernel_main        ; Call kernel_main function
    hlt                     ; Halt the CPU


KERNEL_STACK_SIZE equ 8192

section .bss                ; 'Block Started by Symbol' memory section to declare variable not initialised
resb KERNEL_STACK_SIZE      ; 8KB for stack

stack_space: