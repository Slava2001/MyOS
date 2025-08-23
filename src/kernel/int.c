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

void int_common_handler(int_num, regs) uint int_num; Regs *regs; {
    switch (int_num) {
    case 0x21:
        int_x21_handler(regs);
        break;
    case 0x20:
        int_x20_handler(regs);
        break;
    default:
        loge(("Unsupported interrupt! int: 0x%02x", int_num));
        while (1);
        break;
    }
    return;
}

void int_x21_handler(regs) Regs *regs; {
    switch (regs->a.byte.h) {
    case 0x4B:
        int_x21_x4b_handler(regs);
        break;
    case 0x09:
        int_x21_x09_handler(regs);
        break;
    default:
        loge(("Unsupported interrupt 0x21 subfunction! subfunction: 0x%02x", (uint)regs->a.byte.h));
        while (1);
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
