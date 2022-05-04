#include "math.h"

static word div_result;

word udiv(word a, word b) {
#asm 
    xor dx, dx
    mov bx, sp
    mov ax, [bx+2]
    mov bx, [bx+4]
    div bx
    mov _div_result, ax
#endasm    
    return div_result;
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