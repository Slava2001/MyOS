#include "lunar_os.h"
#include "stdio.h"
#include "string.h"

char *logo = "\n\r"
"                   xxxxxx\n\r"
"               xxxx      xxxx\n\r"
"             xx              xx\n\r"
"            x                  x\n\r"
"           x                    x\n\r"
"          x                      x\n\r"
"          x                      x\n\r"
"           x                    x\n\r"
"            x                  x\n\r"
"             xx              xx\n\r"
"               xxxx      xxxx\n\r"
"               /   xxxxxx    \\\n\r"
"        /--------------------------\\\n\r"
"        |//\\     |        |     /\\\\|\n\r"
"        // \\\\    |        |    // \\\\\n\r"
"       //   []   |        |   []   \\\\\n\r"
"      //\\--------------------------/\\\\\n\r"
"     //  //     //        \\\\     \\\\  \\\\\n\r"
"    //  //     //__________\\\\     \\\\  \\\\\n\r"
"   //  \\__/                      \\__/  \\\\\n\r"
"  //                                    \\\\\n\r"
"\\____/                                \\____/\n\r";

#define BUFF_SIZE 8 + 1 + 3 + 1
int entry() {
    ExecParam exec_param;
    char input_buff[BUFF_SIZE];
    int rc;
    puts(logo);
    puts("Wellcom to Lunar OS terminal!\n\r");

    exec_param.env_seg = 0;
    exec_param.cmd_args_tail = 0;
    exec_param.fcb1 = 0;
    exec_param.fcb2 = 0;
    while(1) {
        puts("A:/>");
        rc = gets(input_buff, BUFF_SIZE - 4);
        if (!rc) {
            continue;
        }
        uppercase(input_buff);
        if (!strcmp(input_buff, "EXIT")) {
            puts("Goodby!\n\r");
            break;
        }
        if (!strcmp(input_buff, "HELP")) {
            puts("HELP:\n\r"
                 "Now this terminal allows you to run *.COM "
                 "applications from the application directory. "
                 "To do this, just enter the program name, for "
                 "example \"keycode\" or \"mem\"\n\r");
            continue;
        }
        memcpy(input_buff + rc, ".COM", 5);
        exec(input_buff, &exec_param);
    }
    return 0;
}
