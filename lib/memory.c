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
    byte i, s;

    for (; i < 80; i++)
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

byte disk_num = 0x80;
byte max_head_num = 0;
byte max_cylinder_num = 0;
byte max_sector_num = 0;

void init_disk() {
#asm 
    mov dl, _disk_num
    mov ah, #$08
    int #$13
    mov _max_head_num, dh
    mov _max_cylinder_num, ch 
    mov _max_sector_num, cl
#endasm
}

void show_disk_info() {
    printf("Disk info:\n\r");
    printf("disk num: 0x");
    printf(hex2char(disk_num, 1));
    printf("\n\rmax head num: ");
    printf(int2char(max_head_num));
    printf("\n\rmax cylinder num: ");
    printf(int2char(max_cylinder_num));
    printf("\n\rmax sector num: ");
    printf(int2char(max_sector_num));
    printf("\n\r");
}


word hd, cy, sc;
void load_sector(desk_ptr, src_sector)word desk_ptr, src_sector; 
{
#asm
    desk_ptr: .word 0x0000
    src_sector: .word 0x0000
    head: .word 0x0000
    cylinder: .word 0x0000
    sector: .word 0x0000
    cyl_count: .word 0x0000

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

    mov cyl_count, ax
    inc dx // sector num start at 1
    mov sector, dx

    xor dx, dx
    mov ax, cyl_count
    mov bx, _max_cylinder_num
    inc bx 
    div bx

    mov head, ax
    mov cylinder, dx

    mov ax, head
    mov _hd, ax
    mov ax, cylinder
    mov _cy, ax
    mov ax, sector  
    mov _sc, ax

    mov dl, _disk_num
    mov dh, head

    // TODO fix cylinder and sector pack
    mov ch, cylinder
    mov cl, sector
    
    mov ax, _cur_seg
    mov es, ax
    mov bx, desk_ptr
    mov al, #$01
    mov ah, #$02
    int #$13
    
#endasm
    printf("head: ");
    printf(int2char(hd));
    printf("\n\rcylinder: ");
    printf(int2char(cy));
    printf("\n\rsector: ");
    printf(int2char(sc));
    printf("\n\rdest: ");
    printf(int2char(desk_ptr));
    printf("\n\r");
}	

read_byte(sec)word sec;
{
    static void * load_sec;
    load_sec = malloc(512);
	load_sector(load_sec, sec);
	printf("ReadByte: ");
	printf(hex2char(*((byte*)load_sec),1));
	printf("\n\r");
    free(load_sec);
}