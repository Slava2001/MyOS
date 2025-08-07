#include "stdio.h"
#include "disk.h"

#if __FIST_ARG_IN_AX__
#error "First arg in AX unsupported!!!"
#endif

#define BOOTLOADER_ADDR (ulong)0x00007e00
#define BOOTLOADER_DISK 0x80

int bootloader_main() {
    DiskCtx disk;
    int rc, i, s;
    char *ptr;

    clear_screen();
    rc = disk_init(&disk, BOOTLOADER_DISK);
    if (rc != 0) {
        printf("Failed to get disk info\n\r");
        while (1);
    }
    printf("Disk info:\n\r    disk_num: %x\n\r    cylinders: %d\n\r    "
           "heads: %d\n\r    sectors: %d\n\r",
           disk.disk_num, disk.cylinders, disk.heads, disk.sectors);
    
    for (s = 0; s < 0x8000; s++) {   
        rc = disk_load(&disk, (ulong)s,  BOOTLOADER_ADDR + 0x1400, 1);
        if (rc != 0) {
            printf("Failed to load sector: error: %d\n\r", rc - 1);
            while (1);
        }
        //puts("Load sector: OK\n\r");
        
        ptr = 0x1400;
        for (rc = 0; rc < 1; rc++) {
            for (i = 0; i < 16; i++) {
                printf("%02x ", (int)*(char *)ptr);
                ptr = ptr + 1;
            }
            puts("\n\r");
        }
        for (rc = 0; rc < 10; rc++) {
            #asm
            hlt
            #endasm
        }
    }

    while(1) {}
    return 0;
}
