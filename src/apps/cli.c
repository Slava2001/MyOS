#include "stdio.h"
#include "lunar_os.h"

int entry() {
    ExecParam p;
    p.env_seg = 0;
    p.cmd_args_tail = 0;
    p.fcb1 = 0;
    p.fcb2 = 0;
    printf("Hello, I am CLI!!!\n\r");
    exec("/KEYCODE.COM", &p);
    printf("Goodbye!!!\n\r");
    return 0;
}
