#include "stdio.h"
#include "types.h"

int entry() {
    uint c;
    puts("Keycode scanner. Press ESC to exit\n\r");
    do {
        c = get_key();
        printf("Key: %c (%d), scancode: %d full code: 0x%04x\n\r",
               c & 0xFF, c & 0xFF, (c >> 8) & 0xFF, c);
    } while(c != KEY_ESC);
    return 0;
}
