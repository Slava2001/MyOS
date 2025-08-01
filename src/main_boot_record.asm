; The main boot record, it copies the OS bootloader into RAM and hands over control to it
use16
org 0x7C00
section .text
; jump on MBR
jmp start
times 3 - ($-$$) db 0
; FAT16 header
times 62 - ($-$$) db 0

start:
    ; setup registers
    cli
        mov AX, CS              
        mov DS, AX             
        mov ES, AX              
        mov SS, AX                 
        mov BP, 0x7C00
        mov SP, 0x7C00           
    sti

    ; print start message
    mov SI, str_start_loading
    call out_asciz

    ; print disk number
    mov SI, str_disk_num
    call out_asciz
    mov AL, DL
    call out_hex_byte
    mov SI, str_new_line
    call out_asciz

jmp $


; 02H читать секторы
;      вход: DL = номер диска (0=диск A...; 80H=тв.диск 0; 81H=тв.диск 1)
;            DH = номер головки чтения/записи
;            CH = номер дорожки (цилиндра)(0-n) =¬
;            CL = номер сектора (1-n) ===========¦== См. замечание ниже.
;            AL = число секторов (в сумме не больше чем один цилиндр)
;            ES:BX => адрес буфера вызывающей программы
;            0:0078 => таблица параметров дискеты (для гибких дисков)
;            0:0104 => таблица параметров тв.диска (для твердых дисков)
;    выход: Carry-флаг=1 при ошибке и код ошибки диска в AH.
;           ES:BX буфер содержит данные, прочитанные с диска
;           замечание: на сектор и цилиндр отводится соответственно 6 и 10 бит:
;                  1 1 1 1 1 1
;                 +5-4-3-2-1-0-9-8-7-6-5-4-3-2-1-0+
;             CX: ¦c c c c c c c c C c S s s s s s¦
;                 +-+-+-+-+-+-+-+-¦-+-+-+-+-+-+-+-+
;                                 +======> исп. как старшие биты номера цилиндра

SECOND_BOOTLOADER_SIZE_SECTORS equ 10

load_second_bootloader:
    ; AH = 0x02 - Read sectors, AL = 40 - 
    mov AH, 0x02 ; Subfunction 0x02 - Read sectors
    mov DL, 0x80 ; Disk number 
    mov DH, 0x00 ; Head number
    mov CX, 0x0C ; Track number 15-6 bit, Sector number - 5-0 bit
    mov AL, SECOND_BOOTLOADER_SIZE_SECTORS; Num of sectors to load
    ES:BX

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





; Outputs char provided in `AL`    
out_char:
    push AX
    mov AH, 0x0E
    int 0x10
    pop AX
ret

; Outputs a null-terminated string whose address is passed in the `SI`
out_asciz:
    push AX
    push SI
    .next_char:
        lodsb
        or AL, AL
        jz .done
        call out_char
        jmp .next_char
    .done:
    pop SI
    pop AX
ret

; Outputs provided in `AL` number (0-f) as hexadecimal digit
out_hex:
    push AX
    and AL, 0xf
    add AL, '0'
    cmp AL, '9'
    jle .not_letter
    add AL, 'A'-'9'-1
    .not_letter:
    call out_char
    pop AX
ret

; Outputs provided in `AL` byte as 2 hexadecimal digits
out_hex_byte:
    push AX
    push AX
    shr AL, 4
    call out_hex
    pop AX
    call out_hex
    pop AX
ret

; Strings
str_disk_num: db "Disk number: ", 0
str_start_loading: db "Start loading bootloader...", 
str_new_line: db 13, 10, 0

times 510 - ($-$$) db 0 
db 0x55, 0xAA