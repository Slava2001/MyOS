#include "disk.h"

struct CHS {
    int cylinder;
    int head;
    int sector;
};

void calc_chs(ctx, lba, chs) 
struct DiskCtx *ctx; unsigned long lba; struct CHS *chs; {
    unsigned long tmp;
    chs->cylinder = lba / (ctx->heads * ctx->sectors);
    tmp = lba % (ctx->heads * ctx->sectors);
    chs->head = tmp / ctx->sectors;
    chs->sector = (tmp % ctx->sectors) + 1;
}

int init_disk(ctx, disk_num)struct DiskCtx *ctx; int disk_num; {
    ctx->disk_num = disk_num;
    return get_disk_info(disk_num, &ctx->cylinders, &ctx->heads, &ctx->sectors);
}

int load(ctx, src_sector, dst)
struct DiskCtx *ctx; unsigned long src_sector, dst; {
    struct CHS chs;
    calc_chs(ctx, src_sector, &chs);
    return 0;
}

int save(ctx, src, dst_sector)
struct DiskCtx *ctx; unsigned long src, dst_sector; {
    struct CHS chs;
    calc_chs(ctx, dst_sector, &chs);
    return 0;
}