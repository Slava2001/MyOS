#include "stdio.h"
#include "types.h"

int entry() {
    uint c;
    printf("Keycode scanner. Press ESC to exit\n\r");
    do {
        c = get_key();
        printf("Key: %c (%d), scancode: %d\n\r",
               c & 0xFF, c & 0xFF, (c >> 8) & 0xFF);
    } while(c != KEY_ESC);
    return 0;
}
