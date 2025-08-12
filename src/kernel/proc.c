#include "proc.h"
#include "utils.h"
#include "fat16.h"
#include "fcall.h"

extern Fat16Ctx FAT;

int prox_exec(path, params) char *path; ExecParam *params; {
    int rc;
    Fat16FileDesc root;
    Fat16FileDesc file;

    logi(("Loading Path: %.128s", path));
    logi(("Params:\n\r    env_seg: 0x%04x\n\r    cmd_args_tail: 0x%08lx\n\r    "
          "cmd_args_tail: 0x%08lx\n\r    cmd_args_tail: 0x%08lx\n\r",
          params->env_seg, params->cmd_args_tail, params->fcb1, params->fcb2));

    rc = fat16_get_root(&FAT, &root);
    reci(rc, ("Failed to get root dir"));

    rc = fat16_find(&FAT, &root, path, &file);
    reci(rc, ("Failed to find program: %s", path));

    rc = fat16_load(&FAT, &file, (ulong)0x00008100, (ulong)1000);
    reci(rc, ("Failed to load program: %s", path));

    logi(("Program %s loaded", path));

    #asm
        mov ax, #$0800
        mov ds, ax
        mov es, ax
        mov ss, ax
        mov sp, 0xffff
        mov bp, 0xffff
        sti
        call #$0800:#$100
    #endasm

    return 0;
}
