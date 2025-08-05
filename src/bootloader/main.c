#include "stdio.h"

#if __FIST_ARG_IN_AX__
#error "First arg in AX unsupported!!!"
#endif

int bootloader_main() {
    long a;
    long b,q;
    int c;
    a = 123;
    b = 123;
    c = 123;

    clear_screen();

    b = 0xff0fff;
    q = 10;
    b = b % q;

    printf("Bootloader started %d\r\n", (int)b);
    while (1);



    if (c%(int)10 == 3) {puts("imod:   OK\n\r");} else {puts("imod:   NOK\n\r");}
    if (a > (long)0 ) {puts("lcmpl:  OK\n\r");} else {puts("lcmpl:  NOK\n\r");}
    if (a+(long)10 == 133) {puts("laddl:  OK\n\r");} else {puts("laddl:  NOK\n\r");}
    if (a-(long)10 == 113) {puts("laddl:  OK\n\r");} else {puts("lsubl:  NOK\n\r");}
    if (b > (unsigned long)0) {puts("lcmpul: OK\n\r");} else {puts("lcmpul: NOK\n\r");}
    if (-a == (long)-123) {puts("lnegl:  OK\n\r");} else {puts("lnegl:  NOK\n\r");}
    if (b+(unsigned long)10 == (unsigned long)133) {puts("laddul: OK\n\r");} else {puts("laddul: NOK\n\r");}
    if (b-(unsigned long)10 == (unsigned long)113) {puts("lsubul: OK\n\r");} else {puts("laddul: NOK\n\r");}
    if (b%(unsigned long)10 == (unsigned long)3) {puts("lmodul: OK\n\r");} else {puts("lmodul: NOK\n\r");}
    if (b/(unsigned long)10 == (unsigned long)12) {puts("ldivul: OK\n\r");} else {puts("ldivul: NOK\n\r");}
    if (a/(long)10 == (long)12) {puts("ldivl:  OK\n\r");} else {puts("ldivl:  NOK\n\r");}
    if (a%(long)10 == (long)3) {puts("lmodl:  OK\n\r");} else {puts("lmodl:  NOK\n\r");}

    printf("test: %%\r\n");
    printf("test: %d\r\n", (int) 123);
    printf("test: %d\r\n", (int)-123);
    printf("test: %u\r\n", (unsigned int)1234);
    printf("test: %ld\r\n", (long)12345);
    printf("test: %lu\r\n", (unsigned long)1234567);
    printf("test: %x\r\n", 0xDEAD);
    printf("test: %lx\r\n", 0xDEADBEAF);
    printf("test: %b\r\n", 0xAAAA);
    printf("test: %lb\r\n", 0xAAAABBBB);
    while(1) {}
    return 0;
}
