void putc(c) int c; {
#asm
    mov ah, #$0e
#if !__FIST_ARG_IN_AX__
    mov bx, sp
    mov al, [bx+2]
#endif
    xor bx, bx
    int #$10
#endasm
}

void clear_screen() {
#asm
	mov al, #$02
    mov ah, #$00
    int #$10
#endasm
}

char now_dir_str[30]="A:zxcxcxczxczxczxczx";
int kernel_main() {
    clear_screen();
    putc('H');
    putc('e');
    putc('l');
    putc('l');
    putc('0');
    putc('!');
    while(1) {}
    return 0;
}
