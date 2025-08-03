use16
section .text
extern _kernel_main
global _main
_main:
    mov AH, 0x0E
    mov AL, 'H'
    int 0x10
    jmp _kernel_main
jmp $
