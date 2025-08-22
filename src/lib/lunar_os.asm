use16
section .text
global _exec

; char *name, ExecParam *param
_exec:
    push BP
    mov BP, SP
    push ES
    push BX
    push DX
    mov AX, DS
    mov ES, AX
    mov AH, 0x4B
    mov AL, 0x00
    mov BX, [BP + 6]
    mov DX, [BP + 4]
    int 0x21
    pop DX
    pop BX
    pop ES
    pop BP
ret
