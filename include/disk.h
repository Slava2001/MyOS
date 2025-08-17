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
 * Set local addres flag (most signed bit)
 * If flag is set addres is relative to current segment, else addres is absolute
 * @param addr linear addres 0x00000-0xFFFFF
 */
#define Local(addr) ((ulong)(0x80000000 + (ulong)((uint)(addr))))

/// RAM linear addres 0x00000-0xFFFFF
typedef ulong RamAddr;

/**
 * Init context for work with disk
 * @param[out] ctx context to init
 * @param disk_num disk number
 * @return -1 on error, else 0
 */
int disk_init(DiskCtx *ctx, int disk_num);

/**
 * Read sectors form disk to RAM
 * @param[in] ctx disk context
 * @param src_sector first sector to load
 * @param dst RAM addres. If the high bit is set, the address is considered
 *            relative to the current segment, otherwise absolute
 * @param sector_count sector count to load
 * @return bios int 0x13 error code + 1 on Nok, 0 on Ok
 */
int disk_load(DiskCtx *ctx, ulong src_sector, RamAddr dst, uint sector_count);

/**
 * Save sectors form RAM to disk
 * @param[in] ctx disk context
 * @param src RAM addres. If the high bit is set, the address is considered
 *            relative to the current segment, otherwise absolute
 * @param dst_sector first destination sector
 * @param sector_count sector count to save
 * @return bios int 0x13 error code + 1 on Nok, 0 on Ok
 */
int disk_save(DiskCtx *ctx, RamAddr src_sector, uint dst, uint sector_count);

#endif // DISK_H
