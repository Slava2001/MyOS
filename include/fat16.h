#ifndef FAT16_H
#define FAT16_H

#include "types.h"
#include "disk.h"

typedef struct Fat16Header {
    byte jmp_on_bootloader[3];
    char os_name[8 + 1 /*for terminated null*/];
    uint bytes_per_sector;
    byte sectors_per_cluster;
    uint system_area_size;
    byte fat_table_count;
    uint descriptions_count_in_root;
    uint total_sectors_count;
    byte device_type;
    uint fat_table_size;
    uint sectors_per_track;
    uint head_count;
    ulong absolute_sector_number;
    ulong disk_size_in_sectors;
    byte disk_number;
    byte reserved;
    byte signature;
    ulong disk_create_date;
    char volume_label[11 + 1 /*for terminated null*/];
    char file_system_type[8 + 1 /*for terminated null*/];
} Fat16Header;

typedef struct Fat16Ctx {
    uint buff_addr;
    Fat16Header header;
    DiskCtx *disk;
} Fat16Ctx;


/**
 * Init Fat16 context
 * @param[in] buff buff for internal data (must be 512 byte)
 * @param len buff len (must be 512)
 * @param[in] disk disk context
 * @param[out] ctx fat 16 context
 * @return -1 on error, else 0
 */
int fat16_init(void *buff, int len, DiskCtx *disk, Fat16Ctx *ctx);

#endif // FAT16_H
