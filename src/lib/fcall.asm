use16
section .text
global _fcall

_fcall:
    push BP
    mov BP, SP
    mov AX, [BP + 4]
    push AX,
    mov AX, [BP + 6]
    push AX
    call FAR [BP - 4]
    add SP, 4
    pop BP
ret
