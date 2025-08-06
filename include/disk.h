#ifndef DISK_H
#define DISK_H

struct DiskCtx {
    int disk_num;
    int cylinders;
    int heads;
    int sectors;
};

int init_disk(struct DiskCtx *ctx, int disk_num);
int load(struct DiskCtx *ctx, unsigned long src_sector, unsigned long dst);
int save(struct DiskCtx *ctx, unsigned long src, unsigned long dst_sector);

#endif // DISK_H