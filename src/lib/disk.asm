use16
section .text
global _get_disk_info
global _load_sectors_from_disk
global _save_sectors_to_disk

; word disk_num, &cylinders, &heads, &sectors
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

; word disk_num, word cylinder, word head,
; word sector, word sector_count, dword dst
_load_sectors_from_disk:
    push BP
    mov BP,SP
    push DI
    push SI

    mov DL, [BP + 4] ; disk number
    mov DH, [BP + 8] ; head number
    mov CL, [BP + 10] ; sector number
    and CL, 111111b
    mov AX, [BP + 6] ; cylinder number
    rol AX, 8
    mov CH, AH
    shl AL, 6
    or CL, AL
    mov BX, [BP + 16] ; dst addr segment
    shl BX, 12
    mov ES, BX
    mov BX, [BP + 14] ; dst addr offset
    mov AL, [BP + 12] ; sector count
    mov AH, 0x02

    int 0x13
    jc .error
       xor AX, AX
       jmp .end
    .error:
       shr AX, 8
       inc AX
    .end:

    pop SI
    pop DI
    pop BP
ret

; word disk_num, word cylinder, word head,
; word sector, word sector_count, dword src
_save_sectors_to_disk:
    mov AX, -1
ret
