#include "string.h"
#include "types.h"

#define push_char(buff, cursor, ch) \
    if (cursor > buff) { cursor--; *cursor = ch; } else { return cursor; }

char* ltoa(val, buff, len, base) long val; char *buff; int len, base; {
    char sign, *cursor;
    sign = 0;
    if (val < 0) {
        sign = 1;
        val =- val;
    }
    cursor = ultoa((ulong)val, buff, len, base);
    if (sign) {
        push_char(buff, cursor, '-')
    }
    return cursor;
}

char* ultoa(val, buff, len, base) ulong val; char *buff; int len, base; {
    char tmp, *cursor;
    cursor = buff + len;
    push_char(buff, cursor, 0);
    do {
        tmp = '0' + val % base;
        if (tmp > '9') {
            tmp += 'A' - '9' - 1;
        }
        push_char(buff, cursor, tmp);
        val = val / base;
    } while (val > 0);
    return cursor;
}

int isdigit(ch) char ch; {
    return ch >= '0' && ch <= '9';
}

void memcpy(dst, src, len) void *src, *dst; uint len; {
    uint i;
    for (i = 0; i < len; i++) {
        ((byte *)dst)[i] = ((byte *)src)[i];
    }
}

void trim_trailing_spaces(str) char *str; {
    char *cursor;
    cursor = str;
    if (!*cursor) {
        return;
    }
    while(*cursor) {
        cursor++;
    }
    do {
        cursor--;
    } while(*cursor == ' ' && cursor >=  str);
    *(++cursor) = 0;
}

uint strlen(str) char *str; {
    uint rc;
    rc = 0;
    while(*str) {
        rc++;
        str++;
    }
    return rc;
}

int strcmp(a, b) char *a, *b; {
    while (*a && *a == *b) {
        a++;
        b++;
    }
    return (int)(*b - *a);
}
