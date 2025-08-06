#include "stdio.h"
#include "disk.h"

#if __FIST_ARG_IN_AX__
#error "First arg in AX unsupported!!!"
#endif

int bootloader_main() {
    struct DiskCtx ctx;
    clear_screen();
    
    printf("Disk info:\n\r    rc: %d\r\n    disk_num: %x\n\r    cylinders: %d\n\r    "
           "heads: %d\n\r    sectors: %d\n\r", init_disk(&ctx, 0x80),
           ctx.disk_num, ctx.cylinders, ctx.heads, ctx.sectors);
    while(1) {}
    return 0;
}
