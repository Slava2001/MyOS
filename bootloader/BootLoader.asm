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
        mov ax,cs              
        mov ds,ax             
        mov es,ax              
        mov ss,ax                 
        mov bp,7c00h
        mov sp,7c00h            
        sti


		
	mov al,dl
	mov [disknum],al						
			

 mov   ax, 0x100        
    mov   es, ax
    mov	  bx, 0
    mov   ch, 0
    mov   cl, 2   
	;mov   dl, 0x80
    mov   dh, 0
call load
 mov   ax, 0x1e0         
    mov   es, ax
    mov	  bx, 0
    mov   ch, 0
    mov   cl, 9  
	;mov   dl, 0x80
    mov   dh, 0
call load
   
    
    pop   ds
    pop   es
    
     mov al, '>'
    mov ah, 0x0E
    mov bh, 0
    int 0x10
	

	
	
    jmp 0x100:0
	
   mov al, '<'
    mov ah, 0x0E
    mov bh, 0
    int 0x10
	jmp$
   
load:

    mov   ah, 2
    mov   al, 7
    int   0x13
			
	
    jnc .no_error
	
    mov al, 8h	
	add al,48

    mov ah, 0x0E
    mov bh, 0
    int 0x10

	 mov al, ah	
	add al,48

    mov ah, 0x0E
    mov bh, 0
    int 0x10
	 mov al, ah	
	add al,49

    mov ah, 0x0E
    mov bh, 0
    int 0x10
		
	mov al,'('

    mov ah, 0x0E
    mov bh, 0
    int 0x10
	
	
	
	
			mov ah,00h
			int 16h
			 mov al, ah	


    mov ah, 0x0E
    mov bh, 0
    int 0x10
			int 16h
			 mov al, ah	


    mov ah, 0x0E
    mov bh, 0
    int 0x10
			int 16h
			 mov al, ah	


    mov ah, 0x0E
    mov bh, 0
    int 0x10
    .no_error:
ret   

finish:
    times 510 - ($-$$) db 0 
    db 0x55, 0xAA
    

	
