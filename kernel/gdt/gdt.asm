[bits 32]

global gdt_init

gdt_init:
    cli
    lgdt [GDT_descriptor]   ; special instruction, declare my gdt

    ; Enable the Protection Enable (PE) bit in Control Register 0 (CR0)
    mov eax, cr0
    or eax, 1       ; PE = 1
    mov cr0, eax
    jmp   0x08:gdt_flush ; far jump

gdt_flush:
    mov ax, 0x10        ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ret


; ===== GDT TABLE ===== ;

    ; TO REMEMBER - ACCESS BYTE
        ;   Access byte, 8 bits which represent : 
        ;   Present bit (P) -> always set to 1
        ;   Descriptor privilege level field (DPL) -> 0 = highest privileges to 3 = lower, 4 values possibles so 2 bits needed
        ;   Descriptor type bit (S) -> 0 = system segment, 1 = code or data segment
        ;   Executable bit (E) -> 0 = data segment, 1 = code segment which can be executed
        ;   Direction bit/conforming bit (DC) ->  for code, 0 = code can be exec from ring set in DPL, 1 = can be exec from equal or lower priv
        ;   Readable bit / writable bite (RW) -> for code, 0 = read not allowed, 1 = read allowed
        ;   Accessed bit -> better set to 1
    ; TO REMEMBER - Granularity + limit high
        ; limit + flag:
        ; limit is 1111
        ; flag -> granularity, set to 1 | size flag 1 = 32 bits, 0 = 16 bits | long mode (64bits) yes = 1, no = 0 | reserved always 0

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
    dw GDT_end - GDT_start - 1  ; size of GDT table     | 16 bits -> should be (8 bytes * 7) - 1 = 55, 0x37
    dd GDT_start                ; beginning of the GDT  | 32 bits
