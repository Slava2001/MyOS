#ifndef FAT16_H
#define FAT16_H

#include "types.h"
#include "disk.h"

typedef struct Fat16Header {
    byte jmp_on_bootloader[3];
    char os_name[8 + 1 /*for terminated null*/];
    uint bytes_per_sector;
    byte sectors_per_cluster;
    uint system_area_size_sectors;
    byte fat_table_count;
    uint descriptions_count_in_root;
    uint total_sectors_count;
    byte device_type;
    uint fat_table_size_sectors;
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

enum FileAttribute {
    FATTR_READONLY     = 1 << 0,
    FATTR_HIDDEN       = 1 << 1,
    FATTR_SYSTEM       = 1 << 2,
    FATTR_VOLUME_LABEL = 1 << 3,
    FATTR_DIR          = 1 << 4,
    FATTR_ARCHIVE      = 1 << 5
};

typedef struct Fat16FileDesc {
    char name[8 + 1 /*for terminated null*/];
    char ext[3 + 1 /*for terminated null*/];
    byte attribute;
    byte create_time_centiseconds;
    uint create_time;
    uint create_date;
    uint last_read_date;
    uint last_write_time;
    uint last_write_date;
    uint first_cluster;
    ulong file_size_bytes;
    struct {
        bool is_root;
    } inner;
} Fat16FileDesc;

typedef struct Fat16Ctx {
    Fat16Header header;
    DiskCtx *disk;
    ulong root_dir_sector;
} Fat16Ctx;

/**
 * Init Fat16 context
 * @param[in] disk disk context
 * @param[out] ctx fat 16 context
 * @return -1 on error, else 0
 */
int fat16_init(DiskCtx *disk, Fat16Ctx *ctx);

/**
 * Get root dir description
 * @param[in] ctx fat 16 context
 * @param[out] root_dir buffer to save root directory description
 * @return -1 on error, else 0
 */
int fat16_get_root(Fat16Ctx *ctx, Fat16FileDesc *root_dir);

/**
 * Get list of files in specifed directory
 * @param[in] ctx fat 16 context
 * @param[in] dir directory description
 * @param skip skip descriptions
 * @param[out] files buffer to save files descriptions
 * @param max_files_count buffer size
 * @return -1 on error, else 0
 */
int fat16_list(
    Fat16Ctx *ctx, Fat16FileDesc *dir, int skip, Fat16FileDesc *files, int max_files_count
);

/**
 * Load one sector of file
 * @param[in] ctx fat 16 context
 * @param[in] file file to read sector
 * @param src_sector file sector to load
 * @param[out] dst destination RAM addres
 * @return -1 on error, else 0
 */
int fat16_load_one(Fat16Ctx *ctx, Fat16FileDesc *file, ulong src_sector, RamAddr dst);

/**
 * Load file
 * @param[in] ctx fat 16 context
 * @param[in] file file to read
 * @param dst destination RAM addres
 * @param dst_size_sectors destinaion size in sectors
 * @return -1 on error, else 0
 */
int fat16_load(Fat16Ctx *ctx, Fat16FileDesc *file, RamAddr dst, ulong dst_size_sectors);

/**
 * Find file by path
 * @param[in] ctx fat 16 context
 * @param[in] dir dir for search
 * @param[in] name file name
 * @param[out] file found file
 * @return -1 on error, 0 if file found, 1 if file not found
 */
int fat16_find(Fat16Ctx *ctx, Fat16FileDesc *dir, char *name, Fat16FileDesc *file);

#endif // FAT16_H
