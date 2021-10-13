#include "graphic.h"
#include "Types.h"

byte *graphic_base = 0xb800;

void set_video_mode(mode)enum video_mode mode; {
#asm
    mov bx, sp
    mov ax, [bx+2]
    xor ah, ah
    int #$10
#endasm
}

word ds;
void draw_point() {

#asm 
   // mov ax, 0x0100
    //mov ds, 0x100
    mov ax, ds
    

    mov ds, 0x100
    mov bx, ptr[0x01]
    mov _ds, bx 



    mov ds, ax
    
#endasm
    printf(hex2char(ds, 2));
}
