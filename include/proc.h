#ifndef PROC_H
#define PROC_H

#include "types.h"

typedef struct ExecParam {
    uint env_seg;
    ulong cmd_args_tail;
    ulong fcb1;
    ulong fcb2;
} ExecParam;

int prox_exec(char *path, ExecParam *params);

#endif // PROC_H
