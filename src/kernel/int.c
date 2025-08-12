#include "int.h"
#include "types.h"
#include "stdio.h"
#include "utils.h"
#include "string.h"
#include "proc.h"

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
void int_x21_x4b_handler(Regs *regs);

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
    case 0x4B:
        return int_x21_x4b_handler(regs);
    default:
        loge(("Unsupported interrupt 0x21 subfunction! subfunction: 0x%02x", (uint)regs->a.byte.h));
        break;
    }
}

void int_x21_x4b_handler(regs) Regs *regs; {
    char name[128];
    ExecParam params;
    strcpy_from_far(name, regs->ds, regs->d.x);
    memcpy_from_far(&params.env_seg,       regs->es, regs->b.x,      2);
    memcpy_from_far(&params.cmd_args_tail, regs->es, regs->b.x + 2,  4);
    memcpy_from_far(&params.fcb1,          regs->es, regs->b.x + 6,  4);
    memcpy_from_far(&params.fcb2,          regs->es, regs->b.x + 10, 4);
    prox_exec(name, &params);
}
