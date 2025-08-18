use16
section .text
global _main
extern _entry
_main:
    call _entry
    mov AH, 0x09
    int 0x21
jmp $
