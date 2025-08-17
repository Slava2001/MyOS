#ifndef INT_H
#define INT_H

#include "types.h"

typedef union Reg {
    uint x;
    struct {
        byte l;
        byte h;
    } byte;
} Reg;

// Don't change the order, it should be like in int.asm
typedef struct Regs {
    Reg a;
    Reg b;
    Reg c;
    Reg d;
    uint si;
    uint di;
    uint sp;
    uint bp;
    uint ds;
    uint ss;
    uint es;
    uint flags;
    uint ret_segment;
    uint ret_offset;
} Regs;

void int_init_ivt(void);

#endif // INT_H
