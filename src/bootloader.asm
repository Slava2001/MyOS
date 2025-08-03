use16
org 0x7E00
jmp start

start:
    mov SI, str_starting_bootloader
    int 0x20
jmp $

str_starting_bootloader: db "Starting bootloader...", 13, 10, 0

SECOND_BOOTLOADER_SIZE_SECTORS equ 10
times 512 * SECOND_BOOTLOADER_SIZE_SECTORS db 0
