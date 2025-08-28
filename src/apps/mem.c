#include "stdio.h"
#include "string.h"
#include "types.h"

#define LINE_LEN 16
#define LINES_PER_SCREEN 24
#define ADDR_MAX 0x100000

void print_line(ulong start_addr);
void print_screen(ulong start_addr);

void print_line(start_addr) ulong start_addr; {
    byte tmp;
    uint seg, offset;
    int i;
    char buff[LINE_LEN + 1];
    seg = (uint)(start_addr / 16);
    offset = (uint)(start_addr % 16);
    buff[LINE_LEN] = 0;
    printf("0x%05lx: ", start_addr);
    for (i = 0; i < LINE_LEN; i++) {
        memcpy_from_far(&tmp, seg, offset, 1);
        printf("%02x ", (uint)tmp);
        buff[i] = '.';
        if (isprint(tmp)) {
            buff[i] = tmp;
        }
        offset = offset + 1;
    }
    printf("  %s\n\r", buff);
}

void print_screen(start_addr) ulong start_addr; {
    int i;
    for (i = 0; i < LINES_PER_SCREEN; i++) {
        print_line(start_addr);
        start_addr = start_addr + LINE_LEN;
    }
}

int entry() {
    ulong addr;
    uint key;
    char buff[6];
    addr = 0;

    clear_screen();
    puts(
        "**************************\n\r"
        "* Memory inspector       *\n\r"
        "* arrow up/down - scroll *\n\r"
        "* g - go to addres       *\n\r"
        "* esc - exit             *\n\r"
        "**************************\n\r"
    );
    print_line(addr);
    addr = addr + LINE_LEN;

    while(1) {
        key = get_key();
        switch (key) {
        case KEY_ARROW_DOWN:
            if (addr <= ADDR_MAX - LINE_LEN) {
                print_line(addr);
                addr = addr + LINE_LEN;
            }
            break;
        case KEY_ARROW_UP:
            if (addr >= (LINES_PER_SCREEN + 1) * LINE_LEN) {
                addr = addr - (LINES_PER_SCREEN + 1) * LINE_LEN;
                print_screen(addr);
                addr = addr + LINES_PER_SCREEN * LINE_LEN;
            }
            break;
        case KEY_G:
            printf("Go to 0x");
            gets(buff, 6);
            addr = ahtoul(buff) / LINE_LEN * LINE_LEN;
            if (addr > ADDR_MAX - LINES_PER_SCREEN * LINE_LEN) {
                addr = ADDR_MAX - LINES_PER_SCREEN * LINE_LEN;
            }
            print_screen(addr);
            addr = addr + LINES_PER_SCREEN * LINE_LEN;
            break;
        case KEY_ESC:
            return 0;
        }
    }
    return 0;
}
