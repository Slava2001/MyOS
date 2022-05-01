#include "math.h"

static word div_result = 0, aa, bb;

word udiv(word a, word b) {
#asm 
    mov bx, sp
    mov ax, [bx+2]
    mov _aa, ax
    mov bx, [bx+4]
    mov _bb, bx
    div bx
    mov _div_result, ax
#endasm    
    return div_result & 0x7fff;
}

static word mod_result = 0;
word umod(word a, word b) {
#asm 
    xor dx, dx
    mov bx, sp
    mov ax, [bx+2]
    mov bx, [bx+4]
    div bx
    mov _mod_result, dx
#endasm
    return mod_result;
}