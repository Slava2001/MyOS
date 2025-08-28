#include "fat16.h"
#include "string.h"
#include "utils.h"
// #define log_lvl Dbg

#define FAT16_SIGNATURE 0x29
#define FILE_DESC_SIZE_BYTE 32
#define SECTOR_SIZE_BYTE 512
#define FILE_DESC_PER_SECTOR ((SECTOR_SIZE_BYTE)/(FILE_DESC_SIZE_BYTE))
#define DELETED_FILE_NAME_FIRST_CHAR 0x5e

#define parse_file_desc(buff, desc) _parse_file_desc((void *)(buff), (Fat16FileDesc *)(desc))
void _parse_file_desc(void *buff, Fat16FileDesc *desc);

#define parse_fat_header(buff, hdr) _parse_fat_header((void *)(buff), (Fat16Header *)(hdr))
void _parse_fat_header(void *buff, Fat16Header *hdr);

#define list_dir(ctx, dir, next_sec_f, desc_count, skip, files, max_files_count) \
    (int)_list_dir((Fat16Ctx *)(ctx), (Fat16FileDesc *)(dir), next_sec_f, (int)(desc_count), \
                   (int)(skip), (Fat16FileDesc *)(files), (int)(max_files_count));
int _list_dir(Fat16Ctx *ctx, Fat16FileDesc *dir, int (*next_sec_f)(), int desc_count, int skip,
               Fat16FileDesc *files, int max_files_count);

#define get_next_cluster(ctx, current, next) \
        (int)_get_next_cluster((Fat16Ctx *)(ctx), (uint)(current), (uint)(next))
int _get_next_cluster(Fat16Ctx *ctx, uint current, uint next);

void _parse_file_desc(buff, desc) void *buff; Fat16FileDesc *desc; {
    memcpy((void *)desc->name,                      (void *)(((byte *)buff) + 0x00), 8 );
    memcpy((void *)desc->ext,                       (void *)(((byte *)buff) + 0x08), 3 );
    memcpy((void *)&desc->attribute,                (void *)(((byte *)buff) + 0x0B), 1 );
    // memcpy((void *)&reserved,                    (void *)(((byte *)buff) + 0x0C), 1 );
    memcpy((void *)&desc->create_time_centiseconds, (void *)(((byte *)buff) + 0x0D), 1 );
    memcpy((void *)&desc->create_time,              (void *)(((byte *)buff) + 0x0E), 2 );
    memcpy((void *)&desc->create_date,              (void *)(((byte *)buff) + 0x10), 2 );
    memcpy((void *)&desc->last_read_date,           (void *)(((byte *)buff) + 0x12), 2 );
    // memcpy((void *)&reserved,                    (void *)(((byte *)buff) + 0x14), 2 );
    memcpy((void *)&desc->last_write_time,          (void *)(((byte *)buff) + 0x16), 2 );
    memcpy((void *)&desc->last_write_date,          (void *)(((byte *)buff) + 0x18), 2 );
    memcpy((void *)&desc->first_cluster,            (void *)(((byte *)buff) + 0x1A), 2 );
    memcpy((void *)&desc->file_size_bytes,          (void *)(((byte *)buff) + 0x1C), 4 );

    desc->name[8] = 0;
    trim_trailing_spaces(desc->name);
    desc->ext[3] = 0;
    trim_trailing_spaces(desc->ext);
    desc->inner.is_root = false;
}

void _parse_fat_header(buff, hdr) void *buff; Fat16Header *hdr; {
    memcpy((void *)hdr->jmp_on_bootloader,           (void *)(((byte *)buff) + 0x00), 3 );
    memcpy((void *)hdr->os_name,                     (void *)(((byte *)buff) + 0x03), 8 );
    memcpy((void *)&hdr->bytes_per_sector,           (void *)(((byte *)buff) + 0x0B), 2 );
    memcpy((void *)&hdr->sectors_per_cluster,        (void *)(((byte *)buff) + 0x0D), 1 );
    memcpy((void *)&hdr->system_area_size_sectors,   (void *)(((byte *)buff) + 0x0E), 2 );
    memcpy((void *)&hdr->fat_table_count,            (void *)(((byte *)buff) + 0x10), 1 );
    memcpy((void *)&hdr->descriptions_count_in_root, (void *)(((byte *)buff) + 0x11), 2 );
    memcpy((void *)&hdr->total_sectors_count,        (void *)(((byte *)buff) + 0x13), 2 );
    memcpy((void *)&hdr->device_type,                (void *)(((byte *)buff) + 0x15), 1 );
    memcpy((void *)&hdr->fat_table_size_sectors,     (void *)(((byte *)buff) + 0x16), 2 );
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

int fat16_init(disk, ctx) DiskCtx *disk; Fat16Ctx *ctx; {
    int rc;
    Fat16FileDesc fd;
    byte buff[512];
    ctx->disk = disk;

    rc = disk_load(ctx->disk, (ulong)0, Local(buff), (uint)1);
    reci(rc, ("Failed to load Fat header: %d", rc));

    parse_fat_header((void *)buff, &ctx->header);
    reci(ctx->header.signature != FAT16_SIGNATURE,
         ("Invalid fat signature: 0x%02x", (uint)ctx->header.signature));

    ctx->root_dir_sector = ctx->header.system_area_size_sectors +
                           ctx->header.fat_table_count*ctx->header.fat_table_size_sectors;
    return 0;
}

int fat16_get_root(ctx, root_dir) Fat16Ctx *ctx; Fat16FileDesc *root_dir; {
    memcpy((void *)root_dir->name, "root", 5);
    root_dir->ext[0] = 0;
    root_dir->attribute = 16;
    root_dir->create_time_centiseconds = 0;
    root_dir->create_time = 0;
    root_dir->create_date = ctx->header.disk_create_date;
    root_dir->last_read_date = 0;
    root_dir->first_cluster = 0;
    root_dir->last_write_time = 0;
    root_dir->last_write_date = 0;
    root_dir->file_size_bytes = ctx->header.descriptions_count_in_root * FILE_DESC_SIZE_BYTE;
    root_dir->inner.is_root = true;
    return 0;
}

int _load_next_sector_root(Fat16Ctx *ctx, Fat16FileDesc *dir, ulong sector, RamAddr dst);
int _load_next_sector_dir(Fat16Ctx *ctx, Fat16FileDesc *dir, ulong sector, RamAddr dst);

int fat16_list(ctx, dir, skip, files, max_files_count)
Fat16Ctx *ctx; Fat16FileDesc *dir; int skip; Fat16FileDesc *files; int max_files_count; {
    int (*next_sec_f)();
    uint desk_cnt, cluster;
    int rc;
    reci(!(dir->attribute & FATTR_DIR),
         ("Failed to get list of files, %s is not a directory", dir->name));
    desk_cnt = ctx->header.descriptions_count_in_root;
    next_sec_f = _load_next_sector_root;
    if (!dir->inner.is_root) {
        next_sec_f = _load_next_sector_dir;
        cluster = dir->first_cluster;
        desk_cnt = FILE_DESC_PER_SECTOR;
        while (1) {
            rc = get_next_cluster(ctx, cluster, &cluster);
            reci(rc, ("Failed to find dir size: failed to get next cluster"));
            if (cluster >= 0xFFF8) {
                break;
            }
            reci((cluster < 0x0003 || cluster > 0xFFEF),
                 ("Failed to find dir size, unexpected fat entry: 0x%04x", cluster));
            desk_cnt += FILE_DESC_PER_SECTOR;
        }
        desk_cnt *= ctx->header.sectors_per_cluster;
        dir->file_size_bytes = (ulong)desk_cnt * FILE_DESC_SIZE_BYTE;
    }
    return list_dir(ctx, dir, next_sec_f, desk_cnt, skip, files, max_files_count);
}

int _load_next_sector_root(ctx, dir, sector, dst)
Fat16Ctx *ctx; Fat16FileDesc *dir; ulong sector; RamAddr dst; {
    int rc;
    rc = disk_load(ctx->disk, ctx->root_dir_sector + sector, dst, (uint)1);
    reci(rc, ("Failed to load root dir sector: %d", rc));
    return 0;
}

int _load_next_sector_dir(ctx, dir, sector, dst)
Fat16Ctx *ctx; Fat16FileDesc *dir; ulong sector; RamAddr dst; {
    int rc;
    rc = fat16_load_one(ctx, dir, sector, dst);
    logd(("load dir file %s sector %lu: rc: %d", dir->name, sector, rc));
    reci(rc, ("Failed to load dir file %s sector: rc: %d", dir->name, rc));
    return 0;
}

int _list_dir(ctx, dir, next_sec_f, desc_count, skip, files, max_files_count)
Fat16Ctx *ctx; Fat16FileDesc *dir; int (*next_sec_f)(); int desc_count; int skip;
Fat16FileDesc *files; int max_files_count; {
    int read_files, i;
    ulong sector;
    int rc, saved_files;
    Fat16FileDesc tmp;
    byte buff[512];

    sector = skip / FILE_DESC_PER_SECTOR;
    i = skip % FILE_DESC_PER_SECTOR;
    saved_files = 0;
    logd(("Sector: %lu, skip: %d", sector, i));
    for (read_files = skip; read_files < desc_count && saved_files < max_files_count;) {
        rc = next_sec_f(ctx, dir, sector, Local(buff));
        reci(rc, ("Failed to load next sector"));
        for (;
             i < FILE_DESC_PER_SECTOR && read_files < desc_count && saved_files < max_files_count;
             i++, read_files++)
        {
            parse_file_desc((void *)(buff + i * FILE_DESC_SIZE_BYTE), &tmp);
            if (tmp.name[0] != 0 && tmp.name[0] != DELETED_FILE_NAME_FIRST_CHAR) {
                files[saved_files] = tmp;
                saved_files++;
            }
        }
        i = 0;
        sector += 1;
    }
    return saved_files;
}

int _get_next_cluster(ctx, current, next)
Fat16Ctx *ctx; uint current, *next; {
    int rc;
    ulong sector, offset;
    byte buff[512];
    sector = ctx->header.system_area_size_sectors + current / ((512 / 2)/*fat entry per sector*/);
    offset = (current % ((512 / 2)/*fat entry per sector*/)) * 2;
    rc = disk_load(ctx->disk, sector, Local(buff), (uint)1);
    reci(rc, ("Failed to load sector with part of fat: %d", rc));
    *next = *((uint *)(buff + offset));
    return 0;
}

int fat16_load_one(ctx, file, src_sector, dst)
Fat16Ctx *ctx; Fat16FileDesc *file; ulong src_sector; RamAddr dst; {
    int rc;
    ulong cluster_sector, offset_in_cluster;
    uint i, cluster_count, cluster;

    reci((src_sector >= (file->file_size_bytes + 511) / 512),
         ("Failed to load file content: sector out of range: "
          "sector: %lu, file size: %lu", src_sector, file->file_size_bytes));

    cluster_count = (uint)(src_sector / ctx->header.sectors_per_cluster);
    cluster = file->first_cluster;
    for (i = 0; i < cluster_count; i++) {
        rc = get_next_cluster(ctx, cluster, &cluster);
        reci((cluster < 0x0003 || cluster > 0xFFEF), ("Unexpected cluster desc: 0x%04x", cluster));
    }
    logd(("Loading sector %lu from cluster %x of file %s", src_sector, cluster, file->name));

    cluster_sector = (ulong)(cluster - 2) * ctx->header.sectors_per_cluster +
                     ctx->root_dir_sector +
                     ((ctx->header.descriptions_count_in_root * FILE_DESC_SIZE_BYTE) /
                      SECTOR_SIZE_BYTE);
    offset_in_cluster = src_sector % ctx->header.sectors_per_cluster;
    src_sector = cluster_sector + offset_in_cluster;

    logd(("Loading sector (on disk: %lx) of file %s", src_sector, file->name));
    logd(("Loading from addr: 0x%08lx", src_sector * 0x200));
    rc = disk_load(ctx->disk, (ulong)src_sector, dst, (uint)1);
    reci(rc, ("Failed to load file content"));
    return 0;
}

int fat16_load(ctx, file, dst, dst_size_sectors)
Fat16Ctx *ctx; Fat16FileDesc *file; RamAddr dst; ulong dst_size_sectors; {
    ulong i, file_size_sectors;
    int rc;
    file_size_sectors = (file->file_size_bytes + 511) / 512;
    reci(dst_size_sectors < file_size_sectors, ("Failed to load file content: provided buffer too "
         "small: required %lu, provided: %lu", file_size_sectors, dst_size_sectors));
    for (i = 0; i < file_size_sectors; i += 1) {
        rc = fat16_load_one(ctx, file, i, dst);
        reci(rc, ("Failed to load %.8s.%.3s files sector: %lu", file->name, file->ext, i));
        dst += SECTOR_SIZE_BYTE;
    }
    return 0;
}

#define FILES_BUFF_SIZE 64

int fat16_find(ctx, dir, name, file)
Fat16Ctx *ctx; Fat16FileDesc *dir; char *name; Fat16FileDesc *file; {
    char file_name[8/*name*/ + 1/*.*/ + 3/*ext*/ + 1/*null*/];
    int name_len, skip, rc, i;
    Fat16FileDesc files[FILES_BUFF_SIZE];

    reci(strlen(name) > 12, ("Unsupported file name: %s", name));

    skip = 0;
    do {
        rc = fat16_list(ctx, dir, skip, files, FILES_BUFF_SIZE);
        skip += rc;
        for (i = 0; i < rc; i++) {
            name_len = strlen(files[i].name);
            memcpy(file_name, files[i].name, name_len + 1);
            if (strlen(files[i].ext)) {
                file_name[name_len] = '.';
                memcpy(file_name + name_len + 1, files[i].ext, strlen(files[i].ext) + 1);
            }
            if (!strcmp(file_name, name)) {
                *file = files[i];
                return 0;
            }
        }
    } while (rc == FILES_BUFF_SIZE);
    reci(rc < 0, ("Failed to list files in %s", dir->name));
    return 1;
}
