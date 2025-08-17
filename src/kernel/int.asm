use16
section .text
global _int_init_ivt
extern _int_common_handler

_int_init_ivt:
    xor AX, AX
    mov ES, AX
    mov word [ES:0x20 * 4    ], _int_handler_0x20
    mov word [ES:0x20 * 4 + 2], CS
    mov word [ES:0x21 * 4    ], _int_handler_0x21
    mov word [ES:0x21 * 4 + 2], CS
    mov word [ES:0x22 * 4    ], _int_handler_0x22
    mov word [ES:0x22 * 4 + 2], CS
    mov word [ES:0x23 * 4    ], _int_handler_0x23
    mov word [ES:0x23 * 4 + 2], CS
    mov word [ES:0x24 * 4    ], _int_handler_0x24
    mov word [ES:0x24 * 4 + 2], CS
    mov word [ES:0x25 * 4    ], _int_handler_0x25
    mov word [ES:0x25 * 4 + 2], CS
    mov word [ES:0x26 * 4    ], _int_handler_0x26
    mov word [ES:0x26 * 4 + 2], CS
    mov word [ES:0x27 * 4    ], _int_handler_0x27
    mov word [ES:0x27 * 4 + 2], CS
ret

_int_handler_0x20:
    mov word [CS:int_num], 0x20
    jmp _int_handler_proxy
_int_handler_0x21:
    mov word [CS:int_num], 0x21
    jmp _int_handler_proxy
_int_handler_0x22:
    mov word [CS:int_num], 0x22
    jmp _int_handler_proxy
_int_handler_0x23:
    mov word [CS:int_num], 0x23
    jmp _int_handler_proxy
_int_handler_0x24:
    mov word [CS:int_num], 0x24
    jmp _int_handler_proxy
_int_handler_0x25:
    mov word [CS:int_num], 0x25
    jmp _int_handler_proxy
_int_handler_0x26:
    mov word [CS:int_num], 0x26
    jmp _int_handler_proxy
_int_handler_0x27:
    mov word [CS:int_num], 0x27
    jmp _int_handler_proxy

int_num:     dw 0x0000
regs_buf:
reg_ax:      dw 0x0000
reg_bx:      dw 0x0000
reg_cx:      dw 0x0000
reg_dx:      dw 0x0000
reg_si:      dw 0x0000
reg_di:      dw 0x0000
reg_sp:      dw 0x0000
reg_bp:      dw 0x0000
reg_ds:      dw 0x0000
reg_ss:      dw 0x0000
reg_es:      dw 0x0000
reg_flags:   dw 0x0000
ret_segment: dw 0x0000
ret_offset:  dw 0x0000

_int_handler_proxy:
    mov [CS:reg_ax], AX
    mov [CS:reg_bx], BX
    mov [CS:reg_cx], CX
    mov [CS:reg_dx], DX
    mov [CS:reg_si], SI
    mov [CS:reg_di], DI
    mov [CS:reg_sp], SP
    mov [CS:reg_bp], BP
    mov [CS:reg_ds], DS
    mov [CS:reg_ss], SS
    mov [CS:reg_es], ES

    mov BP, SP
    mov AX, [BP + 0]
    mov [CS:ret_offset], AX
    mov AX, [BP + 2]
    mov [CS:ret_segment], AX
    mov AX, [BP + 4]
    mov [CS:reg_flags], AX

    mov AX, CS
    mov DS, AX
    mov SS, AX
    mov ES, AX
    mov SP, 0x7700
    mov BP, 0x7700

    push regs_buf
    push word [int_num]
    call _int_common_handler
    add SP, 4

    mov AX, [CS:reg_ax]
    mov BX, [CS:reg_bx]
    mov CX, [CS:reg_cx]
    mov DX, [CS:reg_dx]
    mov SI, [CS:reg_si]
    mov DI, [CS:reg_di]
    mov SP, [CS:reg_sp]
    mov BP, [CS:reg_bp]
    mov DS, [CS:reg_ds]
    mov SS, [CS:reg_ss]
    mov ES, [CS:reg_es]
iret
