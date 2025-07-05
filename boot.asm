[bits 32]

section .multiboot          ; Multiboot specification
    dd 0x1BADB002           ; Magic number '1 BAD BOOT'
    dd 0x0                  ; Flag
    dd -(0x1BADB002 + 0x0)  ; Checksum

section .text               ; Section for executable instructions
global start
extern kernel_main          ; kernel_main function defined in C file

start:
    cli                     ; Block interrupts, clear the IF flag in the EFLAGS register
    mov esp, stack_space    ; Set stack pointer, moves the empty stack_space function into de Stack Pointer
    call kernel_main        ; Call kernel_main function
    hlt                     ; Halt the CPU

section .bss                ; 'Block Started by Symbol' memory section to declare variable not initialised
resb 8192                   ; 8KB for stack

stack_space: