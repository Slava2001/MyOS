// CDisplay.cpp

#include "stdio.h"

void TextOut( 
        const char far* inStrSource, 
        byte            inX, 
        byte            inY,  
        byte            inBackgroundColor, 
        byte            inTextColor,
        bool            inUpdateCursor
        )
{
    byte textAttribute = ((inTextColor) | (inBackgroundColor << 4));
    byte lengthOfString = Strlen(inStrSource);

    __asm
    {		
        push	bp
        mov		al, inUpdateCursor
        xor		bh, bh	
        mov		bl, textAttribute
        xor		cx, cx
        mov		cl, lengthOfString
        mov		dh, inY
        mov		dl, inX  
        mov     es, word ptr[inStrSource + 2]
        mov     bp, word ptr[inStrSource]
        mov		ah,	13h
        int		10h
        pop		bp
    }
}
void ClearScreen()
{
    __asm
    {
        mov     al, 02h
        mov     ah, 00h
        int     10h
    } 
}

void ShowCursor(bool inMode)                               
{
    byte flag = inMode ? 0 : 0x32;

    __asm
    {
        mov     ch, flag
        mov     cl, 0Ah
        mov     ah, 01h
        int     10h
    }
}

void printf(const char *str)
{
	int i=0;
	
	while(str[i]!='\0')
	{
		putc(str[i]);
	i++;}
	
}

char getc(bool out)
{
	char inch='\0';
	
	__asm
		{
			mov ah,00h
			int 16h
			mov inch,al	
		}
	
	if(out&&inch!='\b'&&inch!=0&&inch!='\n')
	putc(inch);
	
	return inch;
}

void putc(char out)
{
	 __asm
		{
			mov al, out
			mov bh,1h
			mov cx,1h
			mov ah,0eh
			int 10h
		}
}

void setCursorPosition(byte X,byte Y)
{
	__asm
		{
			mov bh,0
			mov dh,Y
			mov dl,X
			mov ah,02h
			int 10h
		}
}

int scanf(char *ptr,int l)
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
	printf("\n\r");
	return lenght;
}




