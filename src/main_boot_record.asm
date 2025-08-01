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
    ; setup registers
    cli
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

jmp $

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
str_disk_num: db "Disk number: ", 0
str_start_loading: db "Start loading bootloader...", 
str_new_line: db 13, 10, 0

times 510 - ($-$$) db 0 
db 0x55, 0xAA