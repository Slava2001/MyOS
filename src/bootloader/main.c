#include "stdio.h"

#if __FIST_ARG_IN_AX__
#error "First arg in AX unsupported!!!"
#endif

int bootloader_main() {
    clear_screen();
    printf("Bootloader started\r\n");
    printf("num: %% %d\r\n", 12345);
    printf("num: %% %d\r\n", -3);
    printf("num: %% %d\r\n", 31);
    printf("num: %% %x\r\n", -0xabcd);
    printf("num: %% %b\r\n", 10);
    while(1) {}
    return 0;
}
