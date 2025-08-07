#include "fat16.h"
#include "string.h"

#define FAT16_SIGNATURE 0x29

int fat16_init(buff, len, disk, ctx)
void *buff; int len; DiskCtx *disk; Fat16Ctx *ctx; {
    int rc;
    Fat16Header *h;
    if (len != 512) {
        return -1;
    }
    ctx->buff_addr = buff;
    ctx->disk = disk;

    rc = disk_load(ctx->disk, (ulong)0, ctx->buff_addr, (uint)1);
    if (rc) {
        printf("Failed to load Fat header: %d", rc);
        return -1;
    }

    h = &ctx->header;
    memcpy((void *)h->jmp_on_bootloader,           (void *)(ctx->buff_addr + 0x00), 3            );
    memcpy((void *)h->os_name,                     (void *)(ctx->buff_addr + 0x03), 8            );
    memcpy((void *)&h->bytes_per_sector,           (void *)(ctx->buff_addr + 0x0B), sizeof(uint) );
    memcpy((void *)&h->sectors_per_cluster,        (void *)(ctx->buff_addr + 0x0D), sizeof(byte) );
    memcpy((void *)&h->system_area_size,           (void *)(ctx->buff_addr + 0x0E), sizeof(uint) );
    memcpy((void *)&h->fat_table_count,            (void *)(ctx->buff_addr + 0x10), sizeof(byte) );
    memcpy((void *)&h->descriptions_count_in_root, (void *)(ctx->buff_addr + 0x11), sizeof(uint) );
    memcpy((void *)&h->total_sectors_count,        (void *)(ctx->buff_addr + 0x13), sizeof(uint) );
    memcpy((void *)&h->device_type,                (void *)(ctx->buff_addr + 0x15), sizeof(byte) );
    memcpy((void *)&h->fat_table_size,             (void *)(ctx->buff_addr + 0x16), sizeof(uint) );
    memcpy((void *)&h->sectors_per_track,          (void *)(ctx->buff_addr + 0x18), sizeof(uint) );
    memcpy((void *)&h->head_count,                 (void *)(ctx->buff_addr + 0x1A), sizeof(uint) );
    memcpy((void *)&h->absolute_sector_number,     (void *)(ctx->buff_addr + 0x1C), sizeof(ulong));
    memcpy((void *)&h->disk_size_in_sectors,       (void *)(ctx->buff_addr + 0x20), sizeof(ulong));
    memcpy((void *)&h->disk_number,                (void *)(ctx->buff_addr + 0x24), sizeof(byte) );
    memcpy((void *)&h->reserved,                   (void *)(ctx->buff_addr + 0x25), sizeof(byte) );
    memcpy((void *)&h->signature,                  (void *)(ctx->buff_addr + 0x26), sizeof(byte) );
    memcpy((void *)&h->disk_create_date,           (void *)(ctx->buff_addr + 0x27), sizeof(ulong));
    memcpy((void *)h->volume_label,                (void *)(ctx->buff_addr + 0x2B), 11           );
    memcpy((void *)h->file_system_type,            (void *)(ctx->buff_addr + 0x36), 8            );
    ctx->header.os_name[8] = 0;
    ctx->header.volume_label[11] = 0;
    ctx->header.file_system_type[8] = 0;

    if (h->signature != FAT16_SIGNATURE) {
        printf("Invalid signature: 0x%02x", (uint)h->signature);
        return -1;
    }
    return 0;
}
