#include "int.h"
#include "types.h"
#include "stdio.h"
#include "utils.h"
#include "string.h"
#include "proc.h"
#include "int.h"

void int_x21_handler(Regs *regs);
void int_x20_handler(Regs *regs); // exec proc
void int_x21_x4b_handler(Regs *regs); // exec proc
void int_x21_x09_handler(Regs *regs); // exit from proc
void int_x21_x30_handler(Regs *regs); // return version
void int_x21_x35_handler(Regs *regs); // get int vector

void int_common_handler(int_num, regs) uint int_num; Regs *regs; {
#define CASE(int_num) case 0 ##int_num: int_ ##int_num ##_handler(regs); break
    switch (int_num) {
    CASE(x20);
    CASE(x21);
    default:
        loge(("Unsupported interrupt! int: 0x%02x", int_num));
        while (1);
        break;
    }
    return;
#undef CASE
}

void int_x21_handler(regs) Regs *regs; {
#define CASE(int_num) case 0 ##int_num: int_x21_ ##int_num ##_handler(regs); break
    switch (regs->a.byte.h) {
    CASE(x4b);
    CASE(x09);
    CASE(x30);
    CASE(x35);
    default:
        loge(("Unsupported interrupt 0x21 subfunction! subfunction: 0x%02x", (uint)regs->a.byte.h));
        while (1);
        break;
    }
#undef CASE
}

void int_x21_x4b_handler(regs) Regs *regs; {
    char name[128];
    ExecParam params;
    strcpy_from_far(name, regs->ds, regs->d.x);
    memcpy_from_far(&params.env_seg,       regs->es, regs->b.x,      2);
    memcpy_from_far(&params.cmd_args_tail, regs->es, regs->b.x + 2,  4);
    memcpy_from_far(&params.fcb1,          regs->es, regs->b.x + 6,  4);
    memcpy_from_far(&params.fcb2,          regs->es, regs->b.x + 10, 4);
    proc_exec(name, &params, regs);
}

void int_x20_handler(regs) Regs *regs; {
    int_x21_x09_handler(regs);
}

void int_x21_x09_handler(regs) Regs *regs; {
    ProcSlot* slot;
    slot = proc_fing_slot(regs->ret_segment);
    rci(!slot,,("Failed to fing caller proc slot, caller seg: 0x%04x", regs->ret_segment));
    proc_exit(slot);
}

void int_x21_x30_handler(regs) Regs *regs; {
    regs->a.byte.l = 0x00;
    regs->a.byte.h = 0x00;
}

void int_x21_x35_handler(regs) Regs *regs; {
    memcpy_from_far(&regs->b.x, (uint)0x0000, (uint)4 * regs->a.byte.l, (uint)2);
    memcpy_from_far(&regs->es, (uint)0x0000, (uint)4 * regs->a.byte.l + 2, (uint)2);
}
