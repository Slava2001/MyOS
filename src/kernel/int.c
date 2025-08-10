#include "int.h"
#include "types.h"

// Don't change the order, it should be like in int.asm
typedef struct Regs {
    uint ax;
} Regs;

void int_common_handler(int_num, regs) uint int_num; Regs *regs; {
    return;
}
