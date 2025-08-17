use16
section .text
global _proc_jmp

tmp_ax: dw 0x0000
; *regs
_proc_jmp:
    mov SI, SP
    mov SI, [SI + 2]

    mov SS, [SI + 18] ; + reg_ss
    mov BP, [SI + 14] ; + reg_bp
    mov SP, [SI + 12] ; + reg_sp

    mov AX, [SI + 22] ; + ret_flag
    push AX
    mov AX, [SI + 24] ; + ret_segment
    push AX
    mov AX, [SI + 26] ; + ret_offset
    push AX

    mov AX, [SI +  0] ; + reg_ax
    mov BX, [SI +  2] ; + reg_bx
    mov CX, [SI +  4] ; + reg_cx
    mov DX, [SI +  6] ; + reg_dx
    mov DI, [SI + 10] ; + reg_di

    mov ES, [SI + 20] ; + reg_es
    mov [CS:tmp_ax], AX
    mov AX, [SI +  8] ; + reg_si
    mov DS, [SI + 16] ; + reg_ds
    mov SI, AX
    mov AX, [CS:tmp_ax]

    sti
    iret
jmp $
