#include "stdio.h"

void TextOut( 
        const char * inStrSource, 
        byte            inX, 
        byte            inY,  
        byte            inBackgroundColor, 
        byte            inTextColor,
        bool            inUpdateCursor
        )
{
    byte textAttribute = ((inTextColor) | (inBackgroundColor << 4));
    byte lengthOfString = 10;//Strlen(inStrSource);

    __asm__
	(		
		".intel_syntax noprefix\n\t"
        "push	bp \n\t"
        "mov	al, %0 \n\t"
        "xor	bh, bh	 \n\t"
        "mov	bl, %2 \n\t"
        "xor	cx, cx \n\t"
        "mov	cl, %1 \n\t"
        "mov	dh, %4 \n\t"
        "mov	dl, %5 \n\t"
        "mov    es, word ptr[%3 + 2] \n\t"
        "mov    bp, word ptr[%3] \n\t"
        "mov	ah,	13h \n\t"
        "int	10h \n\t"
        "pop	bp \n\t"
		: "=r"(inUpdateCursor), "=r"(lengthOfString), "=r"(textAttribute), "=r"(lengthOfString), "=r"(inY) , "=r"(inX)
		: "r"(inUpdateCursor), "r"(lengthOfString), "r"(textAttribute), "r"(lengthOfString), "r"(inX) , "r"(inY)
		: "%ax", "%bx", "%dx", "%cx"
	);
}
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

// void printf(const char *str)
// {
// 	int i=0;
	
// 	while(str[i]!='\0')
// 	{
// 		putc(str[i]);
// 		i++;
// 	}
	
// }

// char getc(bool out)
// {
// 	char inch='\0';
	
// 	__asm
// 		{
// 			mov ah,00h
// 			int 16h
// 			mov inch,al	
// 		}
	
// 	if(out && inch != '\b' && inch != 0 && inch != '\n')
// 	putc(inch);
	
// 	return inch;
// }

// void putc(char out)
// {
// 	 __asm
// 		{
// 			mov al, out
// 			mov bh,1h
// 			mov cx,1h
// 			mov ah,0eh
// 			int 10h
// 		}
// }

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

// int scanf(char *ptr, int l)
// {
// 	char getch='\0';
// 	int lenght=0;
// 	while((getch=getc(true))!=13&&lenght<(l-1))
// 	{
// 		if(getch==8)
// 		{
// 			if(lenght>0){
// 			lenght--;
// 			putc('\b');
// 			putc('\0');
// 			putc('\b');}
// 		}else{
// 		ptr[lenght]=getch;
// 		lenght++;
// 		}
// 	}
// 	ptr[lenght]='\0';
// 	printf("\n\r");
// 	return lenght;
// }




