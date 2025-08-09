use16
section .text
global imod
global lcmpl
global laddl
global lcmpul
global lnegl
global laddul
global lsubul
global lsubl
global ldivul
global lmodul
global lmodl
global ldivl
global lmulul

imod:
    cwd
    idiv BX
    mov AX, DX
ret

lcmpl:
    push DX
    mov DX, [DI + 2]
    cmp BX, DX
    jne .done
    mov DX, [DI]
    cmp AX, DX
    .done:
    pop DX
ret


laddl:
laddul:
    add AX, [DI]
    adc BX, [DI + 2]
ret

lsubul:
lsubl:
    sub AX, [DI]
    sbb BX, [DI + 2]
ret

ldivl:
    push DX
    push CX
    push SI
    mov DX, [di + 2]
    mov CX, [di]
    call __i32_divmod
    pop SI
    pop CX
    pop DX
ret

lmodl:
    push DX
    push CX
    push SI
    mov DX, [di + 2]
    mov CX, [di]
    call __i32_divmod
    mov BX, DX
    mov AX, CX
    pop SI
    pop CX
    pop DX
ret

; BX:AX / DX:CX = BX:AX (DX:CX)
;                (SI:DI)
__i32_divmod:
    push BP
    mov BP, SP
    push SI
    push DI
    inc SP
    ; sign flag
    mov byte [BP + 4], 0x00

    ; check first arg sign and invert if it is neg
    test BX, 0x8000
    jz .skip_invert_a
    not AX
    not BX
    add AX, 1
    adc BX, 0
    push AX
    mov AL, byte [BP + 4]
    inc AL
    mov byte [BP + 4], AL
    pop AX
    .skip_invert_a:

    ; check second arg sign and invert if it is neg
    test DX, 0x8000
    jz .skip_invert_b
    not CX
    not DX
    add CX, 1
    adc DX, 0
    push AX
    mov AL, byte [BP + 4]
    inc AL
    mov byte [BP + 4], AL
    pop AX
    .skip_invert_b:

    call __u32_divmod

    ; if sign flag is 1 (1 arg is neg) invert result
    push AX
    xor AX, AX
    mov AL, [BP + 4]
    test AL, 1
    jz .skip_neg_res
    pop AX
    not AX
    not BX
    add AX, 1
    adc BX, 0
    push AX
    .skip_neg_res:
    pop AX

    dec SP
    pop DI
    pop SI
    pop BP
ret

lcmpul:
    push DX
    mov DX, [DI + 2]
    cmp BX, DX
    jne .done
    mov DX, [DI]
    cmp AX, DX
    .done:
    pop DX
ret

lmodul:
    push DX
    push CX
    push SI
    mov DX, [DI + 2]
    mov CX, [DI]
    call __u32_divmod
    mov BX, DX
    mov AX, CX
    pop SI
    pop CX
    pop DX
ret

ldivul:
    push DX
    push CX
    push SI
    mov DX, [di + 2]
    mov CX, [di]
    call __u32_divmod
    pop SI
    pop CX
    pop DX
ret

; BX:AX / DX:CX = BX:AX (DX:CX)
;                (SI:DI)
__u32_divmod:
    push BP
    mov BP, SP
    push SI
    push DI

    xor SI, SI
    xor DI, DI

    .div_loop:
        cmp BX, DX
        jnz .cmp_done
        cmp AX, CX
        .cmp_done:
        jb .div_loop_done
        sub AX, CX
        sbb BX, DX
        add DI, 1
        adc SI, 0
        jmp .div_loop
    .div_loop_done:

    mov DX, BX
    mov CX, AX

    mov BX, SI
    mov AX, DI

    pop DI
    pop SI
    pop BP
ret

lnegl:
    not AX
    not BX
    add AX, 1
    adc BX, 0
ret

lmulul:
    push DX
    push CX
    push SI

    mov SI, AX
    xor CX, CX

    ; a_lo * b_hi
    mov AX, SI
    mul word [DI + 2]
    mov CX, AX

    ; a_hi * b_lo
    mov AX, BX
    mul word [DI]
    add CX, AX

    ; a_lo * b_lo
    mov AX, SI
    mul word [DI]
    add CX, DX

    mov BX, CX

    pop SI
    pop CX
    pop DX
ret
