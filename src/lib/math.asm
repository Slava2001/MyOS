use16
section .text
global imod
global lcmpl
global lmodl
global laddl
global ldivl

imod:
    mov DX, 0
    div BX
    mov AX, DX
ret

lcmpl:
    push BP
    mov BP, SP
    mov AX, [BP + 4]
    mov DX, [BP + 6]

    mov BX, [BP + 0]
    mov CX, [BP + 2]
    add AX, BX
    adc DX, CX
    pop BP
ret

lmodl:
    push BP
    mov BP, SP

    pop BP
ret

laddl:
    push BP
    mov BP, SP
    mov AX, [BP + 4]
    mov DX, [BP + 6]
    mov BX, [BP + 0]
    mov CX, [BP + 2]
    add AX, BX
    adc DX, CX
    pop BP
ret

ldivl:
    push BP
    mov BP, SP

    pop BP
ret
