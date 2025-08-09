#include "utils.h"
#include "disk.h"
#include "fat16.h"

#if __FIST_ARG_IN_AX__
#error "First arg in AX unsupported!!!"
#endif

#define BOOTLOADER_ADDR (ulong)0x00007e00
#define BOOTLOADER_DISK 0x80

void show_dir(dir, files, count)
Fat16FileDesc *dir; Fat16FileDesc *files; uint count; {
    uint i;
    printf("Dir %s:\n\r", dir->name);
    for (i = 0; i < count; i++) {
        printf("   %8s %3s %5lu %08b (%s)\n\r",
               files[i].name, files[i].ext, files[i].file_size_bytes, (uint)files[i].attribute,
               (files[i].attribute & FATTR_DIR)?
               "DIR":
               (files[i].attribute & FATTR_VOLUME_LABEL)? "LABEL": "FILE");
    }
}

int bootloader_main() {
    int rc, i;
    DiskCtx disk;
    char fat_buf[512];
    Fat16Ctx fat;
    Fat16FileDesc files[512];
    Fat16FileDesc root_dir;

    clear_screen();
    rc = disk_init(&disk, BOOTLOADER_DISK);
    reci(rc, ("Failed to get disk info\n\r"));
    logi(("Disk info:\n\r    disk_num: %x\n\r    cylinders: %d\n\r    "
           "heads: %d\n\r    sectors: %d",
           disk.disk_num, disk.cylinders, disk.heads, disk.sectors));

    rc = fat16_init((void *)fat_buf, (int)sizeof(fat_buf), &disk, &fat);
    reci(rc, ("Failed to init fat16 context"));
    logi(("Init Fat 16: Ok, volume label: %s", fat.header.volume_label));

    rc = fat16_get_root(&fat, &root_dir);
    reci(rc < 0, ("Failed to get root dir"));

    rc = fat16_list(&fat, &root_dir, files, (uint)512);
    reci(rc < 0, ("Failed to list files in root dir"));
    show_dir(&root_dir, &files, rc);

    rc = fat16_list(&fat, &files[1], &files[2], (uint)510);
    reci(rc < 0, ("Failed to list files in dir"));
    show_dir(&files[1], &files[2], rc);

    rc = fat16_list(&fat, &files[5], &files[6], (uint)500);
    reci(rc < 0, ("Failed to list files in dir"));
    show_dir(&files[5], &files[6], rc);
    return 0;
}

void entry_point() {
    if (bootloader_main()) {
        loge(("Some error occurred"));
    }
    logi(("*Infinity loop*"));
    while (1);
}
