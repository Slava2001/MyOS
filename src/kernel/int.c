#include "int.h"
#include "types.h"
#include "stdio.h"
#include "utils.h"

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
} Regs;

void int_x21_handler(Regs *regs);

void int_common_handler(int_num, regs) uint int_num; Regs *regs; {
    switch (int_num) {
    case 0x21:
        return int_x21_handler(regs);
    default:
        loge(("Unsupported interrupt! int: 0x%02x", int_num));
        break;
    }
    return;
}

void int_x21_handler(regs) Regs *regs; {
    switch (regs->a.byte.h) {
        // case 0x4B:
        //     break;
    default:
        loge(("Unsupported interrupt 0x21 subfunction! subfunction: 0x%02x", (uint)regs->a.byte.h));
        break;
    }
}
