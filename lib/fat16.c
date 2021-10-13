#include "Types.h"
#include "stdio.h"
#include "string.h"
#include "mem.h"

byte *fat_header;

//fat header
word byte_per_sector;
byte setor_per_cluster;
word reserved_sectror;
byte number_of_fat;
word root_entries;
word total_sectors;

void init_fat() {
    fat_header = (byte*)malloc(512);
    if (!fat_header) {
        printf("Failed to read fat header\n\r");
        return;
    }

    load_sector(fat_header, 0x0000);

    byte_per_sector = fat_header;
    setor_per_cluster = fat_header;
    reserved_sectror = fat_header;
    number_of_fat = fat_header;
    root_entries = fat_header;
    total_sectors = fat_header;
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
}