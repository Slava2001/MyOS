#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define IMG_SIZE_BYTE (1024*1024*16)
#define IMG_SIZE_SECTOR (IMG_SIZE_BYTE/512)

int main() {
    FILE *out = fopen("debug.img", "wb");
    if (!out) {
        printf("Failed to open file.\n");
        return -1;
    }
    printf("Start writing....\n");
    for (uint16_t i = 0; i < IMG_SIZE_SECTOR; i++) {
        printf("%4.2f%%\n", i*100.f/IMG_SIZE_SECTOR);
        
        for(int q = 0; q < 512/sizeof(uint16_t); q++) {
            fwrite(&i, sizeof(uint16_t), 1, out);
        }
    }
    printf("Done!\n");
    return 0;
}