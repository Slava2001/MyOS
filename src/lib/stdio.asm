use16
section .text
global _putc
global _clear_screen

_putc:
    push BP
    mov BP, SP
    mov AH, 0x0e
    mov AL, [BP+4]
    int 0x10
    pop BP
ret

_clear_screen:
    mov AL, 0x02
    mov AH, 0x00
    int 0x10
ret
