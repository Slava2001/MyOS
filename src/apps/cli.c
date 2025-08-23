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

#define BUFF_SIZE 32
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
    input_buff[0] = '/';
    do {
        printf("A:/>");
        rc = gets(input_buff + 1, BUFF_SIZE - 1 - 5);
        if (rc) {
            memcpy(input_buff + 1 + rc, ".COM", 5);
            uppercase(input_buff);
            exec(input_buff, &exec_param);
        }
    } while(strcmp(input_buff, "/EXIT.COM"));

    return 0;
}
