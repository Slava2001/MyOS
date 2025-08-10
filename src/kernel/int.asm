use16
section .text
global _int_init_ivt
extern _int_common_handler

_int_init_ivt:

ret

regs_buf:
reg_ax:    dw 0x0000
reg_bx:    dw 0x0000
reg_cx:    dw 0x0000
reg_dx:    dw 0x0000
reg_si:    dw 0x0000
reg_di:    dw 0x0000
reg_sp:    dw 0x0000
reg_bp:    dw 0x0000
reg_ds:    dw 0x0000
reg_cs:    dw 0x0000
reg_ss:    dw 0x0000
reg_es:    dw 0x0000
reg_flags: dw 0x0000

_int_handler_proxy:
    cli
    sti
iret
