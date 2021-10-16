#include "Types.h"
#include "stdio.h"
#include "string.h"
#include "mem.h"
#include "fat.h"

byte *fat_header;

//fat header
word byte_per_sector;
byte setor_per_cluster;
word reserved_sectror;
byte number_of_fat;
word root_entries;
word total_sectors;
word sector_per_fat;

word current_dir;

void init_fat() {
    fat_header = (byte*)malloc(512);
    if (!fat_header) {
        printf("Failed to read fat header\n\r");
        return;
    }

    load_sector(fat_header, 0x0000);

    byte_per_sector = *(word*)(fat_header + 0x0b);
    setor_per_cluster = *(byte*)(fat_header + 0x0d);
    reserved_sectror = *(word*)(fat_header + 0x0e);
    number_of_fat = *(byte*)(fat_header + 0x10);
    root_entries = *(word*)(fat_header + 0x11);
    total_sectors = *(word*)(fat_header + 0x13);
    sector_per_fat = *(word*)(fat_header + 0x16);
    current_dir = reserved_sectror + number_of_fat*sector_per_fat;
    free(fat_header);    
}

void show_fat_info() {
    printf("BytesPerSector: ");
    printf(hex2char(byte_per_sector, 2));
    printf("\n\r");
    printf("setor_per_cluster: ");
    printf(hex2char(setor_per_cluster, 1));
    printf("\n\r");
    printf("reserved_sectror: ");
    printf(hex2char(reserved_sectror, 2));
    printf("\n\r");
    printf("number_of_fat: ");
    printf(hex2char(number_of_fat, 1));
    printf("\n\r");
    printf("root_entries: ");
    printf(hex2char(root_entries, 2));
    printf("\n\r");
    printf("total_sectors: ");
    printf(hex2char(total_sectors, 2));
    printf("\n\r");   
    printf("sector_per_fat: ");
    printf(hex2char(sector_per_fat, 2));
    printf("\n\r");   
    printf("root_sector: ");
    printf(hex2char(current_dir, 2));
    printf("\n\r"); 
}

void cd() {
    
}

void show_current_dir() {
	
int i=0;
int n=1;

char * dir_ptr;
char * ptr = current_dir;

dir_ptr = (char*)malloc(512);
if (!dir_ptr) {
    printf("Failed to malloc\n\r");
    return;
}

load_sector(dir_ptr, ptr);

while(*dir_ptr!=0) {
				
		printf("     ");

		for(i=0;i<8;i++)
		putc(*(dir_ptr+i));

		if(*(dir_ptr+0x0b)==0x10) {
			printf(" DIR");
		} else {
			putc('.');
			for(;i<11;i++)
			putc(*(dir_ptr+i));
		}
		
		printf("     ");
		printf(hex2char(*(dir_ptr+i),1));
		printf("h\n\r");
		dir_ptr +=32;
		
		n++;
		if(n==16)
		{
			if(getc(false)==27)
			return;
			n=0;
			dir_ptr-=0x200;
			ptr++;
            load_sector(dir_ptr, ptr);
		}
	}	
}
