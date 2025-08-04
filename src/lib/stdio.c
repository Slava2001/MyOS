#include "stdio.h"

void putc(c) char c; {
#asm
    mov ah, #$0e
#if !__FIST_ARG_IN_AX__
    mov bx, sp
    mov al, [bx+2]
#endif
    xor bx, bx
    int #$10
#endasm
}

void clear_screen() {
#asm
    mov al, #$02
    mov ah, #$00
    int #$10
#endasm
}

void puts(str) char *str; {
    while (*str) {
        putc(*str++);
    }
}

/**
 * Print integer in provided buffer
 * @param val value to print
 * @param base base
 * @param buff buffer to store printed value
 * @param len buff len
 * @return pointer to null-terminated string, witch contain val representation in given base
 */
char* print_int(val, base, buff, len) int val; int len, base; char *buff; {
    #define push_char(ch) if (buff > end_ptr) { buff--; *buff = ch; } else { return buff; }
    int sign;
    char tmp;
    char *end_ptr;
    end_ptr = buff;
    sign = val < 0;
    if (sign) {
        val = -val;
    }
    buff = buff + len - 1;
    push_char(0);
    do {
        tmp = '0' + val % base;
        if (tmp > '9') {
            tmp += 'A' - '9' - 1;
        }
        push_char('0' + val % base);
        val = val / base;
    } while (val > 0);
    if (sign) {
        push_char('-');
    }
    return buff;
    #undef push_char
}

#define TMP_BUFF_SIZE 128
void printf(fmt) char *fmt; {
    void *arg_ptr;
    char tmp_buff[TMP_BUFF_SIZE];
    arg_ptr = (void *)(&fmt + 1);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch(*fmt++) {
                case '%':
                    putc('%');
                break;
                case 'd':
                    puts(print_int(*(int *)arg_ptr, 10, tmp_buff, TMP_BUFF_SIZE));
                break;
                case 'x':
                    puts(print_int(*(int *)arg_ptr, 16, tmp_buff, TMP_BUFF_SIZE));
                break;
                case 'b':
                    puts(print_int(*(int *)arg_ptr, 2, tmp_buff, TMP_BUFF_SIZE));
                break;
            }
        } else {
            putc(*fmt++);
        }
    }
}
