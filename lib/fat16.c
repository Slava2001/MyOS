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

    printf("BytesPerSector: ");
    printf(hex2char(*(word*)(fat_header+0x0b), 2));
    printf("\n\r");
    



}