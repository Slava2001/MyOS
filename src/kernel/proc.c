#include "proc.h"
#include "utils.h"

int prox_exec(path, params) char *path; ExecParam *params; {
    logi(("Loading Path: %.128s", path));
    logi(("Params:\n\r    env_seg: 0x%04x\n\r    cmd_args_tail: 0x%08lx\n\r    "
          "cmd_args_tail: 0x%08lx\n\r    cmd_args_tail: 0x%08lx\n\r",
          params->env_seg, params->cmd_args_tail, params->fcb1, params->fcb2));
    return 0;
}
