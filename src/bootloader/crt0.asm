use16
section .text
extern _bootloader_main
global _main
_main:
    jmp _bootloader_main
