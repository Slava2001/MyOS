#include "Types.h"
#include "stdio.h"
#include "string.h"
#include "mem.h"

// byte
// 512 byte - sector
// 65535 byte-80 sector- segment

#define minimum_size 512

dword cur_seg = 0;
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
            printf(hex2char(memory_map[cur_seg][(y * 10 + x)], 1));
            printf(" ");
        }
        printf("\n\r");
    }
}

void *reserv_block(start, end) word start, end;
{
    int i = start;
    memory_map[cur_seg][i] = end - start;
    i++;
    for (; i < end; i++)
    {
        memory_map[cur_seg][i] = 1;
    }
    return start * minimum_size;
}

void *malloc(size) word size;
{
    word count_of_sec = (size - 1) / minimum_size + 1;
    byte i, s;

    for (; i < 80; i++)
    {
        if (memory_map[cur_seg][i] == 0)
        {
            s = i;
            do
            {
                if (memory_map[cur_seg][s] != 0)
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
    byte size = memory_map[cur_seg][start_poz];
    byte i = start_poz;
    for (; i < start_poz + size; i++)
    {
        memory_map[cur_seg][i] = 0;
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