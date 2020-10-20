use16
org 0x7c00
section .text
jmp start
times 3 - ($-$$) db 0 

db 0x4d,0x53,0x44,0x4f,0x53,0x35,0x2e,0x30
db 0x00,0x02
db 0x40
db 0x10,0x00

db 0x02
db 0x00,0x02
db 0x00,0x00
db 0xf8
db 0x7a,0x00
db 0x3f,0x00
db 0xff,0x00
db 0x80
db 0x00,0x00,0x00

db 0x00,0x50,0x1e,0x00
disknum db 0x80
db 0x00
db 0x29
db 0xca,0x71,0xff,0xee
db 0x4e,0x4f,0x20,0x4e,0x41

db 0x4d,0x45,0x20,0x20,0x20,0x20
db 0x46,0x41,0x54,0x31,0x36,0x20,0x20,0x20


start:
 
 
           cli
        mov ax,cs               ; Setup segment registers
        mov ds,ax               ; Make DS correct
        mov es,ax               ; Make ES correct
        mov ss,ax               ; Make SS correct        
        mov bp,7c00h
        mov sp,7c00h            ; Setup a stack
        sti


		
	mov al,dl
	mov [disknum],al						
			

 mov   ax, 0x100         ; сегмент куда пишем
    mov   es, ax
    mov	  bx, 0; адрес куда пишем
    mov   ch, 0; дорожка 0
    mov   cl, 2   ; начиная с сектора 2
	;mov   dl, 0x80; номер диска
    mov   dh, 0; номер головки
call load
 mov   ax, 0x1e0         ; сегмент куда пишем
    mov   es, ax
    mov	  bx, 0; адрес куда пишем
    mov   ch, 0; дорожка 0
    mov   cl, 9   ; начиная с сектора 2
	;mov   dl, 0x80; номер диска
    mov   dh, 0; номер головки
call load
   
    
    pop   ds
    pop   es
    
     mov al, '>'
    mov ah, 0x0E; номер функции BIOS
    mov bh, 0; страница видеопамяти
    int 0x10; выводим символ
	

	
	
    jmp 0x100:0
	
   mov al, '<'
    mov ah, 0x0E; номер функции BIOS
    mov bh, 0; страница видеопамяти
    int 0x10; выводим символ
	jmp$
   
load:

    mov   ah, 2; номер функции
    mov   al, 7;хз почему 7,если больше, не рабоатет.в сумме больше чем один цилиндр,наверно
    int   0x13
			
	
    jnc .no_error
	
    mov al, 8h	
	add al,48

    mov ah, 0x0E; номер функции BIOS
    mov bh, 0; страница видеопамяти
    int 0x10; выводим символ

	 mov al, ah	
	add al,48

    mov ah, 0x0E; номер функции BIOS
    mov bh, 0; страница видеопамяти
    int 0x10; выводим символ
	 mov al, ah	
	add al,49

    mov ah, 0x0E; номер функции BIOS
    mov bh, 0; страница видеопамяти
    int 0x10; выводим символ
		
	mov al,'('

    mov ah, 0x0E; номер функции BIOS
    mov bh, 0; страница видеопамяти
    int 0x10; выводим символ
	
	
	
	
			mov ah,00h
			int 16h
			 mov al, ah	


    mov ah, 0x0E; номер функции BIOS
    mov bh, 0; страница видеопамяти
    int 0x10; выводим символ	mov ah,00h
			int 16h
			 mov al, ah	


    mov ah, 0x0E; номер функции BIOS
    mov bh, 0; страница видеопамяти
    int 0x10; выводим символ	mov ah,00h
			int 16h
			 mov al, ah	


    mov ah, 0x0E; номер функции BIOS
    mov bh, 0; страница видеопамяти
    int 0x10; выводим символ	
    .no_error:
ret   

finish:
    times 510 - ($-$$) db 0 ; тут выравниваем блок кода до размера сектора(512 байт)
    db 0x55, 0xAA; сигнатура загрузочного сектора
    

	
