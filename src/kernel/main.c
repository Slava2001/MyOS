#include "stdio.h"
#include "utils.h"
#include "int.h"
#include "disk.h"
#include "fat16.h"
#include "proc.h"

#if __FIST_ARG_IN_AX__
#error "First arg in AX unsupported!!!"
#endif

char *APP_NAME = "[KERNEL]";

#define BOOTLOADER_DISK 0x80
DiskCtx DISK;
Fat16Ctx FAT;

int init_kernel() {
    int rc;
    Fat16FileDesc file;

    logi(("Initializing IVT"));
    int_init_ivt();
    rc = disk_init(&DISK, BOOTLOADER_DISK);
    reci(rc, ("Failed to get disk info\n\r"));
    logi(("Disk info:\n\r    disk_num: %x\n\r    cylinders: %d\n\r    "
           "heads: %d\n\r    sectors: %d",
           DISK.disk_num, DISK.cylinders, DISK.heads, DISK.sectors));

    rc = fat16_init(&DISK, &FAT);
    reci(rc, ("Failed to init fat16 context"));
    logi(("Init Fat 16: Ok, volume label: %s", FAT.header.volume_label));

    rc = prox_init();
    reci(rc, ("Failed to init proc manager"));
    logi(("Proc manager loaded"));

    rc = fat16_get_root(&FAT, &file);
    reci(rc, ("Failed to get root dir"));
    rc = fat16_find(&FAT, &file, "PATH", &file);
    reci(rc, ("Failed to PATH dir"));
    rc = fat16_list(&FAT, &file, 0, NULL, 0);
    reci(rc, ("Failed to list"));
    rc = fat16_load(&FAT, &file, (ulong)0x30000, (ulong)0xff);
    reci(rc, ("Failed to load dir"));

    logi(("Kernel initialized"));
    return 0;
}

int entry_point() {
    int rc;
    rc = init_kernel();
    if (rc) {
        loge(("Some error occurred"));
    }
    logi(("Leave from kernel initializer"));
    return rc;
}
