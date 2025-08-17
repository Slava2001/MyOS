use16
section .text
extern _entry_point
global _main
_main:
    cli
        mov BX, DS
        mov AX, CS
        mov DS, AX
        mov ES, AX
        mov SS, AX
        mov [tmp_bp], BP
        mov [tmp_sp], SP
        mov SP, 0x7700
        mov BP, 0x7700
        mov [tmp_segment], BX
    sti
    call _entry_point
    mov BX, AX
    cli
        mov AX, [tmp_segment]
        mov SP, [tmp_sp]
        mov BP, [tmp_bp]
        mov DS, AX
        mov ES, AX
        mov SS, AX
    sti
    mov AX, BX
retf

tmp_segment: dw 0x0000
tmp_sp: dw 0x0000
tmp_bp: dw 0x0000
