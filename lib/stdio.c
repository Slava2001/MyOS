#include "stdio.h"


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


// void TextOut( 
//         const char * inStrSource, 
//         byte            inX, 
//         byte            inY,  
//         byte            inBackgroundColor, 
//         byte            inTextColor,
//         bool            inUpdateCursor
//         )
// {
//     byte textAttribute = ((inTextColor) | (inBackgroundColor << 4));
//     byte lengthOfString = 10;//Strlen(inStrSource);

//     __asm__
// 	(		
// 		".intel_syntax noprefix\n\t"
//         "push	bp \n\t"
//         "mov	al, %0 \n\t"
//         "xor	bh, bh	 \n\t"
//         "mov	bl, %2 \n\t"
//         "xor	cx, cx \n\t"
//         "mov	cl, %1 \n\t"
//         "mov	dh, %4 \n\t"
//         "mov	dl, %5 \n\t"
//         "mov    es, word ptr[%3 + 2] \n\t"
//         "mov    bp, word ptr[%3] \n\t"
//         "mov	ah,	13h \n\t"
//         "int	10h \n\t"
//         "pop	bp \n\t"
// 		: "=r"(inUpdateCursor), "=r"(lengthOfString), "=r"(textAttribute), "=r"(lengthOfString), "=r"(inY) , "=r"(inX)
// 		: "r"(inUpdateCursor), "r"(lengthOfString), "r"(textAttribute), "r"(lengthOfString), "r"(inX) , "r"(inY)
// 		: "%ax", "%bx", "%dx", "%cx"
// 	);
// }
// void ClearScreen()
// {
//     __asm
//     {
//         mov     al, 02h
//         mov     ah, 00h
//         int     10h
//     } 
// }

// void ShowCursor(bool inMode)                               
// {
//     byte flag = inMode ? 0 : 0x32;

//     __asm
//     {
//         mov     ch, flag
//         mov     cl, 0Ah
//         mov     ah, 01h
//         int     10h
//     }
// }

void printf(str)char *str; {
	int i=0;
	
	while(str[i]!='\0')
	{
		putc(str[i]);
		i++;
	}
	
}

static char inch='\0';
char getc(out) char out;
{
	
#asm
			mov ah, #$00
			int #$16
			mov _inch,al	
#endasm

	if(out && inch > 31)
	putc(inch);
	
	return inch;
}



// void setCursorPosition(byte X, byte Y)
// {
// 	__asm
// 		{
// 			mov bh,0
// 			mov dh,Y
// 			mov dl,X
// 			mov ah,02h
// 			int 10h
// 		}
// }

int scanf(ptr, l)char *ptr, l;
{
	char getch='\0';
	int lenght=0;
	while((getch=getc(true))!=13&&lenght<(l-1))
	{
		if(getch==8)
		{
			if(lenght>0){
			lenght--;
			putc('\b');
			putc('\0');
			putc('\b');}
		}else{
		ptr[lenght]=getch;
		lenght++;
		}
	}
	ptr[lenght]='\0';
	putc(10);
    putc(13);
	return lenght;
}




