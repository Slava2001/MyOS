#include "stdio.h"

#if __FIST_ARG_IN_AX__
#error "First arg in AX unsupported!!!"
#endif

int bootloader_main() {
    clear_screen();
    printf("test: %%\r\n");
    printf("test: %d\r\n", (int) 123);
    printf("test: %d\r\n", (int)-123);
    printf("test: %u\r\n", (unsigned int)1234);
    printf("test: %ld\r\n", (long)12345);
    printf("test: %ld\r\n", (long)-12345);
    printf("test: %lu\r\n", (unsigned long)1234567);
    printf("test: 0x%x\r\n", 0xDEAD);
    printf("test: 0x%lx\r\n", (unsigned long)0xDEADBEAF);
    printf("test: 0b%b\r\n", 0xAAAA);
    printf("test: 0b%lb\r\n", (unsigned long)0xAAAABBBB);
    while(1) {}
    return 0;
}
