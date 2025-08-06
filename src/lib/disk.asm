use16
section .text
global _get_disk_info

; disk_num, &cylinders, &heads, &sectors
_get_disk_info:
    push BP
    mov BP,SP
    push DI
    push SI

    ; call interrupt
    mov DL, [BP + 4]
    mov AH, 0x08
    int 0x13

    ; calc heads
    xor AX, AX
    mov AL, DH
    mov SI, [BP + 8]
    mov [SI], AX
    
    ; calc cylinders
    mov AX, CX
    ror AX, 8
    shr AH, 6
    mov SI, [BP + 6]
    mov [SI], AX

    ; calc sectors
    mov AX, CX
    and AX, 111111b
    mov SI, [BP + 10]
    mov [SI], AX

    ; return code 
    xor AX, AX 

    pop SI
    pop DI
    pop BP
ret