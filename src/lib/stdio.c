#include "stdio.h"

void puts(str) char *str; {
    while (*str) {
        putc(*str++);
    }
}

#define push_char(ch) \
    if (buff > end_ptr) { buff--; *buff = ch; } else { return buff; }
/**
 * Print integer in provided buffer
 * @param val value to print
 * @param base base
 * @param buff buffer to store printed value
 * @param len buff len
 * @return pointer to null-terminated string, witch contain val 
 *         representation in given base
 */
#define print_func(func_name, val_type)    \
char* func_name(val, base, buff, len)      \
val_type val; int len, base; char *buff; { \
    int sign;                              \
    char tmp;                              \
    char *end_ptr;                         \
    end_ptr = buff;                        \
    sign = val < 0;                        \
    if (sign) {                            \
        val = -val;                        \
    }                                      \
    buff = buff + len - 1;                 \
    push_char(0);                          \
    do {                                   \
        tmp = '0' + val % base;            \
        if (tmp > '9') {                   \
            tmp += 'A' - '9' - 1;          \
        }                                  \
        push_char(tmp);                    \
        val = val / base;                  \
    } while (val > 0);                     \
    if (sign) {                            \
        push_char('-');                    \
    }                                      \
    return buff;                           \
}
print_func(print_lint, long int)
print_func(print_ulint, unsigned long)
#undef push_char

#define TMP_BUFF_SIZE 64
void printf(fmt) char *fmt; {
    char *arg_ptr;
    char tmp_buff[TMP_BUFF_SIZE];
    arg_ptr = (char *)(&fmt + 1);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch(*fmt++) {
                case '%':
                    putc('%');
                break;
                case 'c':
                    putc(*arg_ptr);
                    arg_ptr += sizeof('\0');
                break;
                case 's':
                    puts(*arg_ptr);
                    arg_ptr += sizeof(char*);
                break;
                case 'd':
                    puts(print_lint((long)*(int *)arg_ptr, 10, tmp_buff, 
                                    TMP_BUFF_SIZE));
                    arg_ptr += sizeof(int);
                break;
                case 'u':
                    puts(print_ulint((unsigned long)(*(unsigned int *)arg_ptr), 
                                     10, tmp_buff, TMP_BUFF_SIZE));
                    arg_ptr += sizeof(unsigned int);
                break;
                case 'x':
                    puts(print_ulint((unsigned long)(*(unsigned int *)arg_ptr), 
                                     16, tmp_buff, TMP_BUFF_SIZE));
                    arg_ptr += sizeof(unsigned int);
                break;
                case 'b':
                    puts(print_ulint((unsigned long)(*(unsigned int *)arg_ptr), 
                                     2, tmp_buff, TMP_BUFF_SIZE));
                    arg_ptr += sizeof(unsigned int);
                break;
                case 'l':
                    switch (*fmt++) {
                    case 'd':
                        puts(print_lint(*(long *)arg_ptr, 10, tmp_buff, 
                                        TMP_BUFF_SIZE));
                        arg_ptr += sizeof(long);
                    break;
                    case 'u':
                        puts(print_ulint(*(unsigned long *)arg_ptr, 10, 
                                         tmp_buff, TMP_BUFF_SIZE));
                        arg_ptr += sizeof(unsigned long);
                    break;
                    case 'x':
                        puts(print_ulint(*(unsigned long *)arg_ptr, 16, 
                                         tmp_buff, TMP_BUFF_SIZE));
                        arg_ptr += sizeof(unsigned long);
                    break;
                    case 'b':
                        puts(print_ulint(*(unsigned long *)arg_ptr, 2, 
                                         tmp_buff, TMP_BUFF_SIZE));
                        arg_ptr += sizeof(unsigned long);
                    break;
                    }
                break;
            }
        } else {
            putc(*fmt++);
        }
    }
}
