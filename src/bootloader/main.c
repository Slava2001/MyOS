#include "utils.h"
#include "disk.h"
#include "fat16.h"

#if __FIST_ARG_IN_AX__
#error "First arg in AX unsupported!!!"
#endif

#define BOOTLOADER_ADDR (ulong)0x00007e00
#define BOOTLOADER_DISK 0x80

int bootloader_main() {
    int rc, i;
    DiskCtx disk;
    char fat_buf[512];
    Fat16Ctx fat;
    Fat16FileDesc files[512];

    clear_screen();

    rc = disk_init(&disk, BOOTLOADER_DISK);
    reci(rc, ("Failed to get disk info\n\r"));
    logi(("Disk info:\n\r    disk_num: %x\n\r    cylinders: %d\n\r    "
           "heads: %d\n\r    sectors: %d",
           disk.disk_num, disk.cylinders, disk.heads, disk.sectors));

    rc = fat16_init((void *)fat_buf, (int)sizeof(fat_buf), &disk, &fat);
    reci(rc, ("Failed to init fat16 context"));
    logi(("Init Fat 16: Ok, volume label: %s", fat.header.volume_label));

    rc = fat16_list_root(&fat, &files, (uint)512);
    reci(rc < 0, ("Failed to init fat16 context"));
    for (i = 0; i < rc; i++) {
        printf("   %s %s %08b\n\r", files[i].name, files[i].ext, (uint)files[i].attribute);
    }


    // logi(("Fat info:\n\r"
    //      "  os_name: %s\n\r"
    //      "  bytes_per_sector: %04x\n\r"
    //      "  sectors_per_cluster: %02x\n\r"
    //      "  system_area_size: %04x\n\r"
    //      "  fat_table_count: %02x\n\r"
    //      "  descriptions_count_in_root: %04x\n\r"
    //      "  total_sectors_count: %04x\n\r"
    //      "  device_type: %02x\n\r"
    //      "  fat_table_size: %04x\n\r"
    //      "  sectors_per_track: %04x\n\r"
    //      "  head_count: %04x\n\r"
    //      "  absolute_sector_number: %08lx\n\r"
    //      "  disk_size_in_sectors: %08lx\n\r"
    //      "  disk_number: %02x\n\r"
    //      "  reserved: %02x\n\r"
    //      "  signature: %02x\n\r"
    //      "  disk_create_date: %08lx\n\r"
    //      "  volume_label: %s\n\r"
    //      "  file_system_type: %s\n\r",
    //      (char *)fat.header.os_name,
    //      fat.header.bytes_per_sector,
    //      (uint)fat.header.sectors_per_cluster,
    //      fat.header.system_area_size,
    //      (uint)fat.header.fat_table_count,
    //      fat.header.descriptions_count_in_root,
    //      fat.header.total_sectors_count,
    //      (uint)fat.header.device_type,
    //      fat.header.fat_table_size,
    //      fat.header.sectors_per_track,
    //      fat.header.head_count,
    //      fat.header.absolute_sector_number,
    //      fat.header.disk_size_in_sectors,
    //      (uint)fat.header.disk_number,
    //      (uint)fat.header.reserved,
    //      (uint)fat.header.signature,
    //      fat.header.disk_create_date,
    //      (char *)fat.header.volume_label,
    //      (char *)fat.header.file_system_type
    // ));

    return 0;
}

void entry_point() {
    if (bootloader_main()) {
        loge(("Some error occurred"));
    }
    logi(("*Infinity loop*"));
    while (1);
}
