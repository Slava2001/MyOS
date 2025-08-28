#include "stdio.h"
#include "types.h"
#include "string.h"

void puts(str) char *str; {
    while (*str) {
        putc(*str++);
    }
}

char getc() {
    char ch;
    do {
        ch = get_key();
        if (isprint(ch)) {
            return ch;
        }
    } while(1);
}

char gets(buff, buff_size) char *buff; uint buff_size; {
    uint len;
    int key;
    len = 0;
    buff_size--; // save space for terminated null
    do {
        key = get_key();
        if (key == KEY_ENTER) {
            puts("\n\r");
            break;
        } else if (key == KEY_BACKSPACE) {
            if (len > 0) {
                len--;
                puts("\b \b");
            }
        } else if ((key & 0xff) && isprint(key & 0xff)) {
            if (len >= buff_size) {
                puts("\n\r");
                break;
            }
            buff[len] = key & 0xff;
            putc(buff[len]);
            len++;
        }
    } while (1);
    buff[len] = 0;
    return len;
}

typedef struct FmtDesc {
    char flag;
    int width;
    int precision;
    char type_size;
    char type;
} FmtDesc;

/**
 * Parse fmt
 * @param[in] buff buffer with format
 * @param[out] desc parsed description
 * @return pointer to element in buff, after parsed fmt
 */
char* parse_fmt(char *buff, FmtDesc *desc);

#define TMP_BUFF_SIZE 64
void printf(fmt) char *fmt; {
    char *cursor, *arg_ptr, tmp_buff[TMP_BUFF_SIZE], padding_char;
    FmtDesc fmt_desc;
    int base, padding;
    uint str_len;

    arg_ptr = (char *)(&fmt + 1);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            fmt = parse_fmt(fmt, &fmt_desc);

            switch (fmt_desc.type) {
                case '%':
                    putc('%');
                break;
                case 'c':
                    putc((char)*arg_ptr);
                    arg_ptr += sizeof('\0');
                break;
                case 's':
                    cursor = *(char **)arg_ptr;
                    arg_ptr += sizeof(char *);
                    str_len = strlen(cursor);
                    if (str_len > (uint)fmt_desc.precision && fmt_desc.precision > 0) {
                        str_len = (uint)fmt_desc.precision;
                    }
                    padding = (int)fmt_desc.width - str_len;
                    if (fmt_desc.flag == '-') {
                        for (;padding > 0; padding--) {
                            putc(' ');
                        }
                    }
                    for (;str_len > 0; str_len--) {
                            putc(*cursor);
                            cursor++;
                    }
                    for (;padding > 0; padding--) {
                        putc(' ');
                    }
                break;
                case 'd':
                case 'u':
                case 'x':
                case 'b':
                    switch (fmt_desc.type) {
                        case 'd':
                        case 'u':
                            base = 10;
                        break;
                        case 'x':
                            base = 16;
                        break;
                        case 'b':
                            base = 2;
                        break;
                    }
                    if (fmt_desc.type == 'd') {
                        if (fmt_desc.type_size == 'l') {
                            cursor = ltoa(*(long *)arg_ptr, tmp_buff, TMP_BUFF_SIZE, base);
                            arg_ptr += sizeof(long);
                        } else {
                            cursor = ltoa((long)*(int *)arg_ptr, tmp_buff, TMP_BUFF_SIZE, base);
                            arg_ptr += sizeof(int);
                        }
                    } else {
                        if (fmt_desc.type_size == 'l') {
                            cursor = ultoa(*(ulong *)arg_ptr, tmp_buff, TMP_BUFF_SIZE, base);
                            arg_ptr += sizeof(ulong);
                        } else {
                            cursor = ultoa((ulong)*(uint *)arg_ptr, tmp_buff, TMP_BUFF_SIZE, base);
                            arg_ptr += sizeof(uint);
                        }
                    }

                    if (fmt_desc.flag == '+' &&
                        (fmt_desc.type == 'd' || fmt_desc.type == 'u') && *cursor != '-') {
                        cursor--;
                        *cursor = '+';
                    }

                    if (fmt_desc.flag == '#' && (fmt_desc.type == 'x' || fmt_desc.type == 'b')) {
                        cursor--;
                        *cursor = fmt_desc.type;
                        cursor--;
                        *cursor = '0';
                    }

                    padding = 0;
                    if (fmt_desc.width) {
                        padding = fmt_desc.width - (TMP_BUFF_SIZE - (int)(cursor - tmp_buff)) + 1;
                    }

                    padding_char = ' ';
                    if (fmt_desc.flag == '0') {
                        padding_char = '0';
                    }

                    if (fmt_desc.flag != '-') {
                        for (;padding>0; padding--) {
                            putc(padding_char);
                        }
                    }

                    puts(cursor);
                    for (;padding > 0; padding--) {
                        putc(padding_char);
                    }
                break;
            }
        } else {
            putc(*fmt++);
        }
    }
}

char* parse_fmt(buff, desc) char *buff; FmtDesc *desc; {
    desc->flag = 0;
    desc->width = 0;
    desc->precision = 0;
    desc->type_size = 0;
    desc->type = 0;

    switch (*buff) {
    case '-':
    case '+':
    case ' ':
    case '0':
    case '#':
        desc->flag = *buff;
        buff++;
        if (!*buff) {
            return buff;
        }
    break;
    }

    while (isdigit(*buff)) {
        desc->width = desc->width * 10;
        desc->width += *buff - '0';
        buff++;
        if (!*buff) {
            return buff;
        }
    }

    if (*buff == '.') {
        buff++;
        if (!*buff) {
            return buff;
        }
        while (isdigit(*buff)) {
            desc->precision = desc->precision * 10;
            desc->precision += *buff - '0';
            buff++;
            if (!*buff) {
                return buff;
            }
        }
    }

    if (*buff == 'l') {
        desc->type_size = 'l';
        buff++;
        if (!*buff) {
            return buff;
        }
    }

    switch (*buff) {
    case '%':
    case 'c':
    case 's':
    case 'd':
    case 'u':
    case 'x':
    case 'b':
        desc->type = *buff;
        buff++;
        if (!*buff) {
            return buff;
        }
    break;
    }
    return buff;
}
