global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; 0: Division By Zero Exception | No error code
isr0:
    cli
    push byte 0 ; Dummy error code to keep a uniform stack frame
    push byte 0
    jmp isr_common_stub

; 1: Debug Exception | No error code
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

; 2: Non Maskable Interrupt Exception | No error code
isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub

; 3: Breakpoint Exception | No error code
isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub

; 4: Into Detected Overflow Exception | No error code
isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub

; 5: Out of Bounds Exception | No error code
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub

; 6: Invalid Opcode Exception | No error code
isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_stub

; 7: No Coprocessor Exception | No error code
isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub

; 8: Double Fault Exception | error code
isr8:
    cli
    push byte 8
    jmp isr_common_stub

; 9: Coprocessor Segment Overrun Exception | No error code
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub

; 10: Bad TSS Exception | error code
isr10:
    cli
    push byte 10
    jmp isr_common_stub

; 11: Segment Not Present Exception | error code
isr11:
    cli
    push byte 11
    jmp isr_common_stub

; 12: Stack Fault Exception | error code
isr12:
    cli
    push byte 12
    jmp isr_common_stub

; 13: General Protection Fault Exception | error code
isr13:
    cli
    push byte 13
    jmp isr_common_stub

; 14: Page Fault Exception | error code
isr14:
    cli
    push byte 14
    jmp isr_common_stub

; 15: Unknown Interrupt Exception | no error code
isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub

; 16: Coprocessor Fault Exception | no error code
isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub

; 17: Alignment Check Exception (486+) | no error code
isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_stub

; 18: Machine Check Exception (Pentium/586+) | no error code
isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub

; 19: Reserved Exception | no error code
isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_stub

; 20: Reserved Exception | no error code
isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_stub

; 21: Reserved Exception | no error code
isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_stub

; 22: Reserved Exception | no error code
isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_stub

; 23: Reserved Exception | no error code
isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_stub

; 24: Reserved Exception | no error code
isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_stub

; 25: Reserved Exception | no error code
isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_stub

; 26: Reserved Exception | no error code
isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_stub

; 27: Reserved Exception | no error code
isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_stub

; 28: Reserved Exception | no error code
isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_stub

; 29: Reserved Exception | no error code
isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_stub

; 30: Reserved Exception | no error code
isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_stub

; 31: Reserved Exception | no error code
isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub

; let the assembler know that 'fault_handler' exists in another file
extern fault_handler

; Saves the processor state, sets up for kernel mode segments,
; calls the C-level fault handler, and finally restores the stack frame.
isr_common_stub:

    ; save processor state
    pusha ; save all general registers (eax, ebx, ..., edi)

    ; save segment registers
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10   ; Load the Kernel Data Segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Push esp on the stack to allow fault_handler to access all informations
    mov eax, esp
    push eax
    
    mov eax, fault_handler
    call eax       ; A special call, preserves the 'eip' register

    ; clean CPU state as before interrupt
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa

    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!