#include "disk.h"
#include "stdio.h"

typedef struct CHS {
    int cylinder;
    int head;
    int sector;
} CHS;

/**
 * Calculate CHS addres from LBA
 * @param[in] ctx disk context
 * @param lba linear addres
 * @param[out] chs calculated CHS
 */
void calc_chs(ctx, lba, chs) DiskCtx *ctx; ulong lba; CHS *chs; {
    ulong tmp;
    chs->cylinder = lba / (ctx->heads * ctx->sectors);
    tmp = lba % (ctx->heads * ctx->sectors);
    chs->head = tmp / ctx->sectors;
    chs->sector = (tmp % ctx->sectors) + 1;
}

int disk_init(ctx, disk_num) DiskCtx *ctx; int disk_num; {
    ctx->disk_num = disk_num;
    return get_disk_info(disk_num, &ctx->cylinders, &ctx->heads, &ctx->sectors);
}

int disk_load(ctx, src_sector, dst, sector_count)
DiskCtx *ctx; ulong src_sector, dst; int sector_count; {
    CHS chs;
    calc_chs(ctx, src_sector, &chs);
    return load_sectors_from_disk(
        ctx->disk_num, chs.cylinder, chs.head, chs.sector, sector_count, dst
    );
}

int disk_save(ctx, src, dst_sector, sector_count)
DiskCtx *ctx; ulong src, dst_sector; int sector_count; {
    CHS chs;
    calc_chs(ctx, dst_sector, &chs);
    return save_sectors_to_disk(
        ctx->disk_num, chs.cylinder, chs.head, chs.sector, sector_count, src
    );
}
