; The main boot record, it copies the OS bootloader into RAM and hands over control to it
use16
org 0x7C00
section .text
; jump on MBR
jmp start
times 3 - ($-$$) db 0
; FAT16 header
times 62 - ($-$$) db 0

start:
    cli
        ; setup registers
        mov AX, CS
        mov DS, AX
        mov ES, AX
        mov SS, AX
        mov BP, 0x7C00
        mov SP, 0x7C00
    sti

    ; print start message
    mov SI, str_start_loading
    call out_asciz

    ; print disk number
    mov SI, str_disk_num
    call out_asciz
    mov AL, DL
    call out_hex_byte
    mov SI, str_new_line
    call out_asciz

    ; load second bootloader
    call load_second_bootloader

    ; print ok message
    mov SI, str_load_ok
    call out_asciz
    mov SI, str_new_line
    call out_asciz

    ; cli
    ;     ; setup registers
    ;     mov AX, 0x7E00
    ;     mov CS, AX
    ;     ; mov DS, AX
    ;     ; mov ES, AX
    ; sti

    ; jump on second bootloader
    jmp 0x07E0:0x0

hold:
    cli
    hlt
    jmp hold

SECOND_BOOTLOADER_SIZE_SECTORS equ 10
; Load second bootloader from boot disk, witch number provided in `DL`
; Bootloader must start in second sector an has length 10 sectors
load_second_bootloader:
    pusha
    push ES
    mov AH, 0x02 ; Subfunction 0x02 - Read sectors
    ;   DL       - Disk number, provided as arg
    mov DH, 0x00 ; Head number
    mov CX, 0x02 ; Track number 15-6 bit, Sector number - 5-0 bit
    mov AL, SECOND_BOOTLOADER_SIZE_SECTORS; Num of sectors to load
    mov BX, 0x00
    mov ES, BX
    mov BX, 0x7E00
    int 0x13
    jnc .no_error
        mov SI, str_failed_to_load_sector
        call out_asciz
        mov AL, AH ; AH - error code
        call out_hex_byte;
        mov SI, str_new_line
        call out_asciz
        jmp hold
    .no_error:
    pop ES
    popa
ret

; Outputs char provided in `AL`
out_char:
    push AX
    mov AH, 0x0E
    int 0x10
    pop AX
ret

; Outputs a null-terminated string whose address is passed in the `SI`
out_asciz:
    push AX
    push SI
    .next_char:
        lodsb
        or AL, AL
        jz .done
        call out_char
        jmp .next_char
    .done:
    pop SI
    pop AX
ret

; Outputs provided in `AL` number (0-f) as hexadecimal digit
out_hex:
    push AX
    and AL, 0xf
    add AL, '0'
    cmp AL, '9'
    jle .not_letter
    add AL, 'A'-'9'-1
    .not_letter:
    call out_char
    pop AX
ret

; Outputs provided in `AL` byte as 2 hexadecimal digits
out_hex_byte:
    push AX
    push AX
    shr AL, 4
    call out_hex
    pop AX
    call out_hex
    pop AX
ret

; Strings
str_disk_num: db "Disk number: 0x", 0
str_start_loading: db "Start loading bootloader...",
str_new_line: db 13, 10, 0
str_failed_to_load_sector: db "Failed to load sector, error code: 0x", 0
str_load_ok: db "Second bootloader loaded: OK", 13, 10, 0

times 510 - ($-$$) db 0
db 0x55, 0xAA
