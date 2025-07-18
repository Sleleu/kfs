global idt_flush

idt_flush:
    mov eax, [esp + 4]  ; move arg of size 4 bytes (idt_pointer addr) in eax
    lidt [eax]
    sti                 ; activate interrupts
    ret

;; --------------------- ISR MACRO --------------------- ;;

%macro isr_no_error_code_handler 1
    global isr%1

    isr%1:
        cli
        push dword 0        ; push 0 as error code
        push dword %1       ; push interrupt number
        jmp isr_common_stub ; jump to the common handler
%endmacro

%macro isr_error_code_handler 1
    global isr%1

    isr%1:
        cli
        push dword %1       ; push interrupt number
        jmp isr_common_stub ; jump to the common handler
%endmacro

;; ----------------------------------------------------- ;;


;; --------------------- IRQ MACRO --------------------- ;;

%macro irq 2
    global irq%1

    irq%1:
        cli
        push dword 0
        push dword %2
        jmp irq_common_stub
%endmacro

;; -------------------- CALL MACROS -------------------- ;;

isr_no_error_code_handler 0
isr_no_error_code_handler 1
isr_no_error_code_handler 2
isr_no_error_code_handler 3
isr_no_error_code_handler 4
isr_no_error_code_handler 5
isr_no_error_code_handler 6
isr_no_error_code_handler 7

isr_error_code_handler 8

isr_no_error_code_handler 9

isr_error_code_handler 10
isr_error_code_handler 11
isr_error_code_handler 12
isr_error_code_handler 13
isr_error_code_handler 14

isr_no_error_code_handler 15
isr_no_error_code_handler 16
isr_no_error_code_handler 17
isr_no_error_code_handler 18
isr_no_error_code_handler 19
isr_no_error_code_handler 20
isr_no_error_code_handler 21
isr_no_error_code_handler 22
isr_no_error_code_handler 23
isr_no_error_code_handler 24
isr_no_error_code_handler 25
isr_no_error_code_handler 26
isr_no_error_code_handler 27
isr_no_error_code_handler 28
isr_no_error_code_handler 29
isr_no_error_code_handler 30
isr_no_error_code_handler 31

irq 0, 32
irq 1, 33
irq 2, 34
irq 3, 35
irq 4, 36
irq 5, 37
irq 6, 38
irq 7, 39
irq 8, 40
irq 9, 41
irq 10, 42
irq 11, 43
irq 12, 44
irq 13, 45
irq 14, 46
irq 15, 47

;; ----------------------------------------------------- ;;

KERNEL_DATA_SEG equ 0x10

extern isr_handler  ; function in C
isr_common_stub:
    pusha           ; push all registers to the stack
    mov eax, ds
    push eax
    mov eax, cr2
    push eax

    mov ax, KERNEL_DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp        ; push stack pointer on stack

    call isr_handler ; call isr_handler function in C

    add esp, 8
    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa            ; pop all registers
    add esp, 8
    sti             ; enable interruptions
    iret


extern irq_handler  ; function in C
irq_common_stub:
    pusha           ; push all registers to the stack
    mov eax, ds
    push eax
    mov eax, cr2
    push eax

    mov ax, KERNEL_DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp        ; push stack pointer on stack

    call irq_handler ; call irq_handler function in C

    add esp, 8
    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa            ; pop all registers
    add esp, 8
    sti             ; enable interruptions
    iret