#include "proc.h"
#include "utils.h"
#include "fat16.h"
#include "fcall.h"
#include "int.h"

extern Fat16Ctx FAT;

#define MAX_PROC_COUNT 2
ProcSlot procs[MAX_PROC_COUNT];

void proc_jmp(Regs *regs);

int prox_init() {
    procs[0].free = true;
    procs[0].segment = 0x07E0;
    procs[0].len = 0xFFFF;
    procs[1].free = true;
    procs[1].segment = 0x17E0;
    procs[1].len = 0xFFFF;
    return 0;
}

int proc_exec(path, params, regs) char *path; ExecParam *params; Regs *regs; {
    int rc;
    Fat16FileDesc root;
    Fat16FileDesc file;
    ProcSlot *slot;
    Regs state;
    ulong load_addr;

    logi(("Loading Path: %.128s", path));

    rc = fat16_get_root(&FAT, &root);
    reci(rc, ("Failed to get root dir"));

    rc = fat16_find(&FAT, &root, path, &file);
    reci(rc, ("Failed to find program: %s", path));

    slot = NULL;
    for (rc = 0; rc < MAX_PROC_COUNT; rc++) {
        if (procs[rc].free) {
            slot = &procs[rc];
            break;
        }
    }
    reci(!slot, ("Failed to find empty slot"));

    slot->free = false;
    slot->parent_state = *regs;
    state = *regs;
    state.sp = slot->len;
    state.bp = slot->len;
    state.ds = slot->segment;
    state.ss = slot->segment;
    state.es = slot->segment;
    state.ret_segment = slot->segment;
    state.ret_offset = 0x100; // for *.COM files

    load_addr = ((ulong)state.ret_segment) * 16 + state.ret_offset;
    rc = fat16_load(&FAT, &file, load_addr, (ulong)slot->len);
    reci(rc, ("Failed to load program: %s", path));

    logi(("Program %s loaded on 0x%08lx(0x%04x:0x%04x)",
          path, load_addr, state.ret_segment, state.ret_offset));
    proc_jmp(&state);

    return -1; // unrectheble
}

ProcSlot* proc_fing_slot(code_segment) uint code_segment; {
    int i;
    for (i = 0; i < MAX_PROC_COUNT; i++) {
        if (procs[i].segment == code_segment) {
            return &procs[i];
        }
    }
    return NULL;
}

void proc_exit(slot) ProcSlot* slot; {
    slot->parent_state.a.x = 0;
    // caller stack hold iret flag, segment and offset
    // proc_jmp use provided flag, segment and offset to jmp
    // so, we need to remove old values from caller stack (6 bytes)
    slot->parent_state.sp += 6;
    proc_jmp(&slot->parent_state);
}
