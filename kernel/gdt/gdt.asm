global gdt_init

KERNEL_CODE_SEG equ kernel_code - GDT_start
KERNEL_DATA_SEG equ kernel_data - GDT_start

gdt_init:
    cli
    lgdt [GDT_descriptor]   ; special instruction, declare my gdt

    ; Enable the Protection Enable (PE) bit in Control Register 0 (CR0)
    mov eax, cr0
    or eax, 1       ; PE = 1
    mov cr0, eax
    jmp   KERNEL_CODE_SEG:gdt_flush ; far jump


[bits 32] ; start protected mode

gdt_flush:
    mov ax, KERNEL_DATA_SEG  ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ret


section .gdt

GDT_start:

    null_segment:       ; GDTR offset + 0x00
        dd 0
        dd 0            ; all 0 | 64 bits

    kernel_code:        ; GDTR offset + 0x08
        dw 0xFFFF       ; limit low                                                         | 16 bits
        dw 0x0000       ; base low                                                          | 16 bits
        db 00000000b    ; base middle                                                       | 8 bits
        db 10011010b    ; access byte = 0x9A    | P=1, DPL=00, S=1, Ex=1, DC=0, RW=1, A=0   | 8 bits
        db 11001111b    ; flag + limit = 0xCF   | G=1, DB=1, L=0, AVL=0 + limit_high        | 8 bits
        db 00000000b    ; base high                                                         | 8 bits

    kernel_data:        ; GDTR offset + 0x10
        dw 0xFFFF
        dw 0x0000
        db 00000000b
        db 10010010b    ; access byte = 0x92    | P=1, DPL=00, S=1, Ex=0, DC=0, RW=1, A=0
        db 11001111b    ; flag + limit = 0xCF
        db 00000000b

    kernel_stack:       ; GDTR offser + 0x18
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 10010010b    ; same as kernel data
        db 11001111b    ; same as kernel data
        db 0x00

    user_code:          ;GDTR offset + 0x20
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 11111010b    ; access byte = 0xFA    | P=1, DPL=11 (ring 3), S=1, Ex=1, RW=1, A=0
        db 11001111b    ; flag + limit = 0xCF
        db 0x00

    user_data:          ; GDTR offset 0x28
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 11110010b   ; access byte = 0xF2     | P=1, DPL=11 (ring 3), S=1, Ex=0, RW=1, A=0
        db 11001111b   ; flag + limit = 0xCF
        db 0x00

    user_stack:          ; GDTR offset 0x30
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 11110010b        ; same as user_data
        db 11001111b        ; same as user data
        db 0x00

GDT_end:


; ===== GDT descriptor (GDTR) =====

GDT_descriptor:
    dw GDT_end - GDT_start - 1  ; maximal offset        | 16 bits -> should be GDT_SIZE - 1 = 55, 0x37
    dd GDT_start                ; beginning of the GDT  | 32 bits
