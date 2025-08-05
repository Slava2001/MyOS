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
    mov AX, CX
    mov BX, DX
    pop SI
    pop CX
    pop DX
ret

; BX:AX / DX:CX = AX:BX (CX:DX)
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

    xor SI, SI
    xor DI, DI

    .div_loop:
        cmp BX, DX
        jne .cmp_done
        cmp AX, CX
        .cmp_done:
        jl .div_loop_done
        sub AX, CX
        sbb BX, DX
        add DI, 1
        adc SI, 0
    jmp .div_loop
    .div_loop_done:

    mov DX, BX
    mov CX, AX

    ; if sign flag is 1 (1 arg is neg) invert result
    xor AX, AX
    mov AL, [BP + 4]
    test AL, 1
    jz .skip_neg_res
    not DI
    not SI
    add DI, 1
    adc SI, 0
    .skip_neg_res:

    mov BX, SI
    mov AX, DI

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
    mov DX, [di + 2]
    mov CX, [di]
    call __u32_divmod
    mov AX, CX
    mov BX, DX
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

; BX:AX / DX:CX = AX:BX (CX:DX)
__u32_divmod:
    push BP
    mov BP, SP
    push SI
    push DI

    xor SI, SI
    xor DI, DI

    .div_loop:
        ; push SI
        ; push AX
        ; mov SI, str_arg_a
        ; call out_asciz
        ; mov AX, BX
        ; call out_hex_word    
        ; pop AX
        ; call out_hex_word
        ; mov SI, str_nl
        ; call out_asciz
        ; pop SI
        
        cmp BX, DX
        jne .cmp_done
        cmp AX, CX
        .cmp_done:
        jl .div_loop_done
        sub AX, CX
        sbb BX, DX
        add DI, 1
        adc SI, 0
    jmp .div_loop
    .div_loop_done:

    push SI
    push AX
    mov SI, str_arg_a
    call out_asciz
    mov AX, BX
    call out_hex_word    
    pop AX
    call out_hex_word
    mov SI, str_nl
    call out_asciz
    pop SI

    mov DX, BX
    mov CX, AX

    mov BX, SI
    mov AX, DI

    push SI
    push AX
    mov SI, str_arg_a
    call out_asciz
    mov AX, BX
    call out_hex_word    
    pop AX
    call out_hex_word
    mov SI, str_nl
    call out_asciz
    pop SI

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


str_arg_a: db "a: 0x", 0
str_arg_b: db "b: 0x", 0
str_arg_r: db "r: 0x", 0
str_nl: db 10, 13, 0
str_a_is_neg: db "a is neg", 10, 13, 0
str_b_is_neg: db "b is neg", 10, 13, 0

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

; Outputs provided in `AX` word as 4 hexadecimal digits
out_hex_word:
    push AX
    push AX
    shr AX, 8
    call out_hex_byte
    pop AX
    call out_hex_byte
    pop AX
ret