#include "fat16.h"
#include "string.h"
#include "utils.h"

#define FAT16_SIGNATURE 0x29


void parse_file_desc(buff, desc) void *buff; Fat16FileDesc *desc; {
    uint first_cluster_h, first_cluster_l;
    memcpy((void *)desc->name,                      (void *)(((byte *)buff) + 0x00), 8 );
    memcpy((void *)desc->ext,                       (void *)(((byte *)buff) + 0x08), 3 );
    memcpy((void *)&desc->attribute,                (void *)(((byte *)buff) + 0x0B), 1 );
    memcpy((void *)&desc->reserved,                 (void *)(((byte *)buff) + 0x0C), 1 );
    memcpy((void *)&desc->create_time_centiseconds, (void *)(((byte *)buff) + 0x0D), 1 );
    memcpy((void *)&desc->create_time,              (void *)(((byte *)buff) + 0x0E), 2 );
    memcpy((void *)&desc->create_date,              (void *)(((byte *)buff) + 0x10), 2 );
    memcpy((void *)&desc->last_read_date,           (void *)(((byte *)buff) + 0x12), 2 );
    memcpy((void *)&first_cluster_h,                (void *)(((byte *)buff) + 0x14), 2 );
    memcpy((void *)&desc->last_write_time,          (void *)(((byte *)buff) + 0x16), 2 );
    memcpy((void *)&desc->last_write_date,          (void *)(((byte *)buff) + 0x18), 2 );
    memcpy((void *)&first_cluster_l,                (void *)(((byte *)buff) + 0x1A), 2 );
    memcpy((void *)&desc->file_size_bytes,          (void *)(((byte *)buff) + 0x1C), 4 );

    desc->first_cluster = (ulong)first_cluster_h;
    desc->first_cluster = desc->first_cluster << 16;
    desc->first_cluster += first_cluster_l;
    desc->name[8] = 0;
    desc->ext[3] = 0;
}

void parse_fat_header(buff, hdr) void *buff; Fat16Header *hdr; {
    memcpy((void *)hdr->jmp_on_bootloader,           (void *)(((byte *)buff) + 0x00), 3 );
    memcpy((void *)hdr->os_name,                     (void *)(((byte *)buff) + 0x03), 8 );
    memcpy((void *)&hdr->bytes_per_sector,           (void *)(((byte *)buff) + 0x0B), 2 );
    memcpy((void *)&hdr->sectors_per_cluster,        (void *)(((byte *)buff) + 0x0D), 1 );
    memcpy((void *)&hdr->system_area_size,           (void *)(((byte *)buff) + 0x0E), 2 );
    memcpy((void *)&hdr->fat_table_count,            (void *)(((byte *)buff) + 0x10), 1 );
    memcpy((void *)&hdr->descriptions_count_in_root, (void *)(((byte *)buff) + 0x11), 2 );
    memcpy((void *)&hdr->total_sectors_count,        (void *)(((byte *)buff) + 0x13), 2 );
    memcpy((void *)&hdr->device_type,                (void *)(((byte *)buff) + 0x15), 1 );
    memcpy((void *)&hdr->fat_table_size,             (void *)(((byte *)buff) + 0x16), 2 );
    memcpy((void *)&hdr->sectors_per_track,          (void *)(((byte *)buff) + 0x18), 2 );
    memcpy((void *)&hdr->head_count,                 (void *)(((byte *)buff) + 0x1A), 2 );
    memcpy((void *)&hdr->absolute_sector_number,     (void *)(((byte *)buff) + 0x1C), 4 );
    memcpy((void *)&hdr->disk_size_in_sectors,       (void *)(((byte *)buff) + 0x20), 4 );
    memcpy((void *)&hdr->disk_number,                (void *)(((byte *)buff) + 0x24), 1 );
    memcpy((void *)&hdr->reserved,                   (void *)(((byte *)buff) + 0x25), 1 );
    memcpy((void *)&hdr->signature,                  (void *)(((byte *)buff) + 0x26), 1 );
    memcpy((void *)&hdr->disk_create_date,           (void *)(((byte *)buff) + 0x27), 4 );
    memcpy((void *)hdr->volume_label,                (void *)(((byte *)buff) + 0x2B), 11);
    memcpy((void *)hdr->file_system_type,            (void *)(((byte *)buff) + 0x36), 8 );
    hdr->os_name[8] = 0;
    hdr->volume_label[11] = 0;
    hdr->file_system_type[8] = 0;
}

int fat16_init(buff, len, disk, ctx)
void *buff; int len; DiskCtx *disk; Fat16Ctx *ctx; {
    int rc;
    Fat16FileDesc fd;

    reci(len != 512, ("Wrong buff len"));
    ctx->buff_addr = buff;
    ctx->disk = disk;

    rc = disk_load(ctx->disk, (ulong)0, ctx->buff_addr, (uint)1);
    reci(rc, ("Failed to load Fat header: %d", rc));

    parse_fat_header((void *)ctx->buff_addr, &ctx->header);
    reci(ctx->header.signature != FAT16_SIGNATURE,
         ("Invalid fat signature: 0x%02x", (uint)ctx->header.signature));

    ctx->root_dir_sector = ctx->header.system_area_size +
                           ctx->header.fat_table_count*ctx->header.fat_table_size;
    return 0;
}

int fat16_list_root(Fat16Ctx *ctx, Fat16FileDesc *files, int max_files_count) {
    uint files_count, read_files, i;
    ulong sector;
    int rc, saved_files;
    Fat16FileDesc tmp;

    sector = ctx->root_dir_sector;
    files_count = ctx->header.descriptions_count_in_root;
    saved_files = 0;
    for (read_files = 0; read_files < files_count;) {
        rc = disk_load(ctx->disk, sector, ctx->buff_addr, (uint)1);
        reci(rc, ("Failed to load root dir sector: %d", rc));
        for (i = 0;
             i < 16 && read_files < files_count && saved_files < max_files_count;
             i++, read_files++)
        {
            parse_file_desc((void *)(ctx->buff_addr + i * 32), &tmp);
            if (tmp.name[0] != 0 && tmp.name[0] != 0xe5) {
                files[saved_files] = tmp;
                saved_files++;
            }
        }
        sector += 1;
    }
    return saved_files;
}

int fat16_load_file(Fat16Ctx *ctx, char *path, uint dts) {
    return -1;
}

int fat16_load_file_g(Fat16Ctx *ctx, char *path, ulong dst) {
    return -1;
}
