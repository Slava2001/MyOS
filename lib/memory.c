#include "Types.h"
#include "stdio.h"
#include "string.h"
#include "mem.h"

// byte
// 512 byte - sector
// 65535 byte-80 sector- segment

#define minimum_size 512

dword cur_seg = 0x100;
dword cur_seg_ind = 0;


byte memory_map[][80] = {{10, 1, 1, 1, 1, 1, 1, 1, 1, 1, // kernel
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

void show_memory_map()
{
    byte x, y;
    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 10; x++)
        {
            printf(hex2char(memory_map[cur_seg_ind][(y * 10 + x)], 1));
            printf(" ");
        }
        printf("\n\r");
    }
}

void *reserv_block(start, end) word start, end;
{
    int i = start;
    memory_map[cur_seg_ind][i] = end - start;
    i++;
    for (; i < end; i++)
    {
        memory_map[cur_seg_ind][i] = 1;
    }
    return start * minimum_size;
}

void *malloc(size) word size;
{
    word count_of_sec = (size - 1) / minimum_size + 1;
    byte i = 0, s;

    for (i = 10; i < 80; i++) // i=10 - save kernel XD
    {
        if (memory_map[cur_seg_ind][i] == 0)
        {
            s = i;
            do
            {
                if (memory_map[cur_seg_ind][s] != 0)
                {
                    break;
                }
                s++;
            } while ((s - i) < count_of_sec && s < 80);
            if (s - i == count_of_sec)
            {
                return reserv_block(i, s);
            }
        }
    }
    return NULL;
}

void free(start) word start;
{
    byte start_poz = start / minimum_size;
    byte size = memory_map[cur_seg_ind][start_poz];
    byte i = start_poz;
    for (; i < start_poz + size; i++)
    {
        memory_map[cur_seg_ind][i] = 0;
    }
}

word disk_num = 0x80;
word max_head_num = 0;
word max_cylinder_num = 0;
word max_sector_num = 0;

void init_disk() {
#asm 
    mov dl, _disk_num
    mov ah, #$08
    int #$13
    mov _max_head_num, dh
    mov _max_cylinder_num, cx
#endasm
    max_sector_num = max_cylinder_num & 0x3f;
    max_cylinder_num = max_cylinder_num >> 6;              
}

void show_disk_info() {
    printf("Disk info:\n\r");
    printf("disk num: 0x");
    printf(hex2char(disk_num, 2));
    printf("\n\rmax head num: ");
    printf(hex2char(max_head_num, 2));
    printf("\n\rmax cylinder num: ");
    printf(hex2char(max_cylinder_num, 2));
    printf("\n\rmax sector num: ");
    printf(hex2char(max_sector_num, 2));
    printf("\n\r");
}


static word hd, cy, sc, er;
void load_sector(desk_ptr, src_sector)word desk_ptr, src_sector; 
{
    // if(desk_ptr < 0x1400) {
    //     printf("Ow shit, im sorry. Overwrite kernel?\n\r");
    // }
#asm
    desk_ptr: .word 0x0000
    src_sector: .word 0x0000
    head: .word 0x0000
    cylinder: .word 0x0000
    sector: .word 0x0000
    head_count: .word 0x0000

    mov bx, sp
    mov ax, [bx+2]
    mov desk_ptr, ax

    mov bx, sp
    mov ax, [bx+4]
    mov src_sector, ax
    
    xor dx, dx
    mov ax, src_sector
    mov bx, _max_sector_num
    div bx 

    mov head_count, ax
    inc dx // sector num start at 1
    mov sector, dx

    xor dx, dx
    mov ax, head_count
    mov bx, _max_head_num
    inc bx 
    div bx

    mov cylinder, ax
    mov head, dx

    mov ax, head
    mov _hd, ax
    mov ax, cylinder
    mov _cy, ax

    mov dl, _disk_num
    mov dh, head

    // TODO fix cylinder and sector pack
    mov cl, #$6
    shl ax, cl
    or ax, sector
 //   mov ax, sector  
    mov _sc, ax

    mov cx, ax
    
    mov ax, _cur_seg
    mov es, ax
    mov bx, desk_ptr
    mov al, #$01
    mov ah, #$02
    int #$13
    
    mov _er, ah

#endasm

    // printf("head: ");
    // printf(hex2char(hd, 2));
    // printf("\n\rcylinder: ");
    // printf(hex2char(cy, 2));
    // printf("\n\rsector: ");
    // printf(hex2char(sc, 2));
    // printf("\n\rerrpr: ");
    // printf(hex2char(er, 2));
    // printf("\n\rsrc: ");
    // printf(hex2char(src_sector, 2));
    // printf("\n\rdest: ");
    // printf(hex2char(desk_ptr, 2));
    // printf("\n\r\n\r");
}	

void read_byte(sec)word sec;
{
    static void * load_sec;
    load_sec = malloc(512);
    if (!load_sec) {
        printf("Failed to malloc\n\r");
        return;
    }
	load_sector(load_sec, sec);
	printf("ReadByte: ");
	printf(hex2char(*(byte*)load_sec, 1));
	printf("\n\r");
    free(load_sec);
}