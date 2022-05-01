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

    mov si, str_load_data
    mov cx, [str_load_data_len]
    call outs

	mov al,dl
	mov [disknum],al

    call load

    mov si, str_loading_sucses
    mov cx, [str_loading_sucses_len]
    call outs

    cli
        mov ax, 0x100             
        mov ds,ax             
        mov es,ax              
        mov ss,ax                 
        mov bp,7c00h
        mov sp,0xffff           
    sti

    jmp 0x100:0
    
jmp $

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
    call out
	
    mov al, '<'
    call out
	
load:

    mov ax, 0x240        
    mov   es, ax
    mov	  bx, 0
	mov   dl, [disknum]
    mov   dh, 0
    mov   ch, 0
    mov   cl, 12   
    mov   al, 10
    mov   ah, 2
    int   0x13	

    mov ax, 0x100        
    mov   es, ax
    mov	  bx, 0
	mov   dl, [disknum]
    mov   dh, 0
    mov   ch, 0
    mov   cl, 2   
    mov   al, 10
    mov   ah, 2
    int   0x13	

    jnc .no_error
	
    mov si, str_failed_to_load_sector
    mov cx, [str_failed_to_load_sector_len]
    call outs

    mov al, ah
    call outHex

    .no_error:
ret   
out:
    push ax
    mov ah, 0x0E
    int 0x10
    pop ax
ret
outHex:
    push ax
    add al, 48
    cmp al, 57
    jle outHex_skip
    add al, 7
    outHex_skip:
    call out
    pop ax
ret
outs:
    push ax
outs_cont:
    mov al, [si]
    call out 
    inc si
    loop outs_cont
    pop ax
ret
;;;str_data;;;
str_load_data: db "Loading os...",0xa,0xd
str_load_data_len: dw ($-str_load_data)
str_failed_to_load_sector: db "Failed to load sector: 0x0"
str_failed_to_load_sector_len: dw ($-str_failed_to_load_sector)
str_loading_sucses: db 0xa,0xd,"Loading os sucsess"
str_loading_sucses_len: dw ($-str_loading_sucses)
finish:
    times 510 - ($-$$) db 0 
    db 0x55, 0xAA
    times 512 db 0
