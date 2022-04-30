#include "stdio.h"

void putc(int c) {
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

void printf(char *str) {
	int i=0;
	
	while(str[i]!='\0')
	{
		putc(str[i]);
		i++;
	}
}

static char inch='\0';
char getc(char out) {
#asm
	mov ah, #$00
	int #$16
	mov _inch,al	
#endasm
	
	if (out && inch > 31) {
		putc(inch);
	} 

	return inch;
}

int scanf(char *ptr, char l) {
	char getch='\0';
	int lenght=0;
	while((getch=getc(true))!=13&&lenght<(l-1)) {
		if (!getch) continue;

		if (getch == 8) {
			if(lenght>0){
			lenght--;
			putc('\b');
			putc('\0');
			putc('\b');}
		} else {
			ptr[lenght]=getch;
			lenght++;
		}
	}
	ptr[lenght]='\0';
	putc(10);
    putc(13);
	return lenght;
}
