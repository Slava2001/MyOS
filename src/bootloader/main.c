#include "utils.h"
#include "disk.h"
#include "fat16.h"
#include "fcall.h"

#if __FIST_ARG_IN_AX__
#error "First arg in AX unsupported!!!"
#endif

#define BOOTLOADER_DISK 0x80

#define KERNEL_SEGMENT (ulong)0x0050
#define KERNEL_OFFSET (ulong)0x0000
#define KERNEL_ADDRES (KERNEL_SEGMENT << 4 + KERNEL_OFFSET)
#define KERNEL_MAX_SIZE (ulong)60

int bootloader_main() {
    int rc;
    DiskCtx disk;
    char fat_buf[512];
    Fat16Ctx fat;
    Fat16FileDesc files[512];
    Fat16FileDesc root_dir;
    Fat16FileDesc *kernel;

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

    kernel = NULL;
    for (rc-- ;rc >= 0; rc--) {
        if (!strcmp(files[rc].name, "KERNEL") && !strcmp(files[rc].ext, "BIN")) {
            kernel = &files[rc];
            logi(("Kernel found. size: %lu bytes", kernel->file_size_bytes));
            break;
        }
    }
    reci(!kernel, ("Kernel not found!"));
    rc = fat16_load(&fat, kernel, KERNEL_ADDRES, KERNEL_MAX_SIZE);
    reci(rc, ("Failed to load kernel"));
    logi(("Kernel loaded"));

    logi(("Call kernel init function"));
    rc = fcall(KERNEL_SEGMENT, KERNEL_OFFSET);
    reci(rc, ("Failed to init kernel"));
    logi(("Kernel initialized"));
    return 0;
}

int entry_point() {
    int rc;
    rc = bootloader_main();
    if (rc) {
        loge(("Some error occurred"));
    }
    logi(("Leave from bootloader"));
    return rc;
}
