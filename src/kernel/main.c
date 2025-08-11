#include "stdio.h"
#include "utils.h"
#include "int.h"

#if __FIST_ARG_IN_AX__
#error "First arg in AX unsupported!!!"
#endif

char *APP_NAME = "[KERNEL]";

int init_kernel() {
    logi(("Initializing IVT"));
    int_init_ivt();
    logi(("Kernel initialized"));
    return 0;
}

int entry_point() {
    int rc;
    rc = init_kernel();
    if (rc) {
        loge(("Some error occurred"));
    }
    logi(("Leave from kernel initializer"));
    return rc;
}
