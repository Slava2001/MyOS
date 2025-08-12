use16
section .text
global _memcpy_from_far
global _strcpy_from_far


; void *dst, uint segment, uint offset, uint len
_memcpy_from_far:
    push BP
    mov BP, SP
    push DI
    push SI

    mov CX, [BP + 10]
    mov DI, [BP + 4]
    mov ES, [BP + 6]
    mov SI, [BP + 8]

    .copy_loop:
        mov AL, [ES:SI]
        mov [DI], AL
        inc SI
        inc DI
    loop .copy_loop

    pop SI
    pop DI
    pop BP
ret
; char *dst, uint segment, uint offset
_strcpy_from_far:
        push BP
    mov BP, SP
    push DI
    push SI

    mov DI, [BP + 4]
    mov ES, [BP + 6]
    mov SI, [BP + 8]

    .copy_loop:
        mov AL, [ES:SI]
        mov [DI], AL
        inc SI
        inc DI
        cmp AL, 0
    jne .copy_loop

    pop SI
    pop DI
    pop BP
ret
