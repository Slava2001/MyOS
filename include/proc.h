#ifndef PROC_H
#define PROC_H

#include "types.h"
#include "int.h"

typedef struct ExecParam {
    uint env_seg;
    ulong cmd_args_tail;
    ulong fcb1;
    ulong fcb2;
} ExecParam;

typedef struct ProcSlot {
    bool free;
    uint segment;
    uint len;
    Regs parent_state;
} ProcSlot;

int prox_init();
int proc_exec(char *path, ExecParam *params, Regs *regs);
ProcSlot* proc_fing_slot(uint code_segment);
void proc_exit(ProcSlot* slot);

#endif // PROC_H
