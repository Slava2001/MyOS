#ifndef DISK_H
#define DISK_H

#include "types.h"

typedef struct DiskCtx {
    int disk_num;
    int cylinders;
    int heads;
    int sectors;
} DiskCtx;

/**
 * Init context for work with disk
 * @param[out] ctx context to init
 * @param disk_num disk number
 * @return -1 on Nok, 0 on Ok
 */
int disk_init(DiskCtx *ctx, int disk_num);

/**
 * Read sectors form disk to RAM
 * @param[in] ctx disk context
 * @param src_sector first sector to load
 * @param dst RAM addres (it is absolute addres with of RAM (not segment offset))
 * @param sector_count sector count to load
 * @return bios int 0x13 error code + 1 on Nok, 0 on Ok
 */
int disk_load(DiskCtx *ctx, ulong src_sector, ulong dst, int sector_count);

/**
 * Write sectors to disk from RAM
 * @param[in] ctx disk context
 * @param src RAM addres (it is absolute addres with of RAM (not segment offset))
 * @param dst_sector start sector to writing
 * @param sector_count sector count to write
 * @return bios int 0x13 error code + 1 on Nok, 0 on Ok
 */
int disk_save(DiskCtx *ctx, ulong src, ulong dst_sector, int sector_count);

#endif // DISK_H
