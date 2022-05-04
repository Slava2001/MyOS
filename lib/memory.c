#include "types.h"
#include "stdio.h"
#include "string.h"
#include "memmory.h"
// #include "math.h"

// byte
// 512 byte - sector
// 65535 byte-80 sector- segment

#define minimum_size 512

dword cur_seg = 0x100;
dword cur_seg_ind = 0;

byte memory_map[][80] = {{20, 1, 1, 1, 1, 1, 1, 1, 1, 1, // kernel
                          1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 3, 1, 1}}; // stack

void show_memory_map() {
    byte y,x;
    for (y = 0; y < 8; y++) {
        for (x = 0; x < 10; x++) {
            printf(hex2char(memory_map[cur_seg_ind][(y * 10 + x)], 1));
            printf(" ");
        }
        printf("\n\r");
    }
}

void *reserv_block(word start, word end) {
    int i = start;
    memory_map[cur_seg_ind][i] = end - start;
    i++;
    for (; i < end; i++) {
        memory_map[cur_seg_ind][i] = 1;
    }
    return start * minimum_size;
}

void *malloc(word size) {
    byte i;
    word count_of_sec = (size - 1) / minimum_size + 1;

    for (i = 20; i < 80; i++) { // i=20 - save kernel XD 
        if (memory_map[cur_seg_ind][i] == 0) {
            byte s = i;
            do {
                if (memory_map[cur_seg_ind][s] != 0) {
                    break;
                }
                s++;
            } while ((s - i) < count_of_sec && s < 80);
            if (s - i == count_of_sec) {
                return reserv_block(i, s);
            }
        }
    }
    return NULL;
}

void free(word start) {
    byte start_poz = start / minimum_size;
    byte size = memory_map[cur_seg_ind][start_poz];
    byte i = start_poz;
    if (start <= 20) {
        printf("Failed to free. it kermel memory\n\r");
        return;
    }
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
    mov ah, #$00
    int #$13

    mov dl, _disk_num
    mov ah, #$08
    int #$13
    mov _max_head_num, dh
    mov _max_sector_num, cl
    mov _max_cylinder_num, ch
#endasm
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

void show_memory() {
    char a = '\0';
    int i;
	byte *ptr = 0x0;

	clear_screen();
	printf("Enter ESC to end. Use \'W\' and \'S\'\n\r");

	while(a != 27) {
		a = getc(false);
		if (a == 'w' || a == 's' || a == 'W' || a == 'S') {
			if (a == 'w') {
				ptr-=32;
            }
			if (a == 'W') {
				ptr-=16*17;
            }
			if (a == 'S') {
				ptr+=16*15;
            }

			printf(hex2char(ptr, 2));
			printf(": ");

			for (i = 0; i < 16; i++) {
				printf(hex2char(*ptr, 1));
				printf(" ");
				ptr++;
			}
			printf("    ");
			ptr-=16;
			for (i = 0; i < 16; i++) {
                if (*ptr>32) {
                    putc(*ptr);
                } else {
                    putc('.');
                }
                ptr++;
			}
			printf("\n\r");
		}
	}
	clear_screen();
	return;
}


/*
00H последняя операция выполнена без ошибок
01H плохая команда: неверный запрос к контроллеру
02H плохая адресная марка
03H защита записи: попытка записи на защищенную дискету
04H ID сектора запорчен или не найден.
05H ошибка сброса -- _AT_
08H сбой DMA
09H перекрытие DMA: попытка записи через 64K-байтовую границу.
0bH встретился флаг плохой дорожки -- _AT_
10H сбой CRC: несовпадение контрольной суммы данных.
11H данные исправлены; исправимая ошибка; исправлено алгоритмом ECC -- _AT_
20H сбой контроллера
40H неудачный поиск. Запрошенная дорожка не найдена
80H Таймаут. Устройство не ответило
0bbH неопределенная ошибка -- _AT_
0ffH сбой операции опроса (sense) -- _AT_
*/
static word hd = 0, cy = 0, sc = 0, er = 0, cx = 0, dp = 0;
int load_sector(word desk_ptr, word src_sector) {
    dp = desk_ptr;
    cy = udiv(src_sector, ((max_head_num+1) * max_sector_num));
    hd = udiv(src_sector, max_sector_num);
    hd = umod(udiv(src_sector, max_sector_num), (max_head_num+1));
    sc = umod(src_sector, max_sector_num) + 1;
    cx = (cy << 8) | (sc & 0xff);

#asm
    mov dl, _disk_num
    mov dh, _hd
    mov cx, _cx
    mov ax, _cur_seg
    mov es, ax
    mov bx, _dp
    mov al, #$01
    mov ah, #$02
    int #$13
    mov _er, ah
#endasm
    if (er) {
        printf("head: ");
        printf(hex2char(hd, 2));
        printf("\n\rcylinder: ");
        printf(hex2char(cy, 2));
        printf("\n\rsector: ");
        printf(hex2char(sc, 2));
        printf("\n\rcx reg: ");
        printf(hex2char(cx, 2));
        printf("\n\rerrpr: ");
        printf(hex2char(er, 2));
        printf("\n\rsrc: ");
        printf(hex2char(src_sector, 2));
        printf("\n\rdest: ");
        printf(hex2char(desk_ptr, 2));
        printf("\n\r");
    }
    return er;
}	

// require a specially prepared image
void load_sector_test() {
	uint16_t i;
	uint8_t rc;

	void *ptr = malloc(512);
	if (!ptr) {
		printf("Failed to malloc\n\r");
		return;
	}

	show_disk_info();

	for (i = 0; i < 32767 && !rc; i++) {
		rc = load_sector(ptr, i);
		if (rc) {
			printf("Failed to load sector. Err: ");
			printf(hex2char(rc,1));
			printf("\n\r");
			return;
		}
		printf("exp: ");
		printf(hex2char(i,2));
		printf(" loaded: ");
		printf(hex2char(*((uint16_t*)ptr), 2));
		printf("\n\r");
		if (i != *((uint16_t*)ptr))
		getc(false);
	}
	free(ptr);
}
