[bits 32]

global inb

inb:
    mov dx, [esp + 4]   ; Move I/O port adress to dx register
    in al, dx           ; read a byte from I/O port and store it in al register
    ret                 ; return