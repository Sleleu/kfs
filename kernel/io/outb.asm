global outb

; outb(uint16_t port, uint8_t data)
; send the byte 'data' to the I/O port 'port'.
outb:
    mov al, [esp + 8]   ; load second arg (data) in al register
    mov dx, [esp + 4]   ; load first arg (port) in dx register
    out dx, al          ; send value in al to dx
    ret                 ; return