#include "stdio.h"
#include "utils.h"

#if __FIST_ARG_IN_AX__
#error "First arg in AX unsupported!!!"
#endif

int init_kernel() {
    logi(("=========Kernel started!========="));
    return 0;
}

int entry_point() {
    int rc;
    rc = init_kernel();
    if (rc) {
        loge(("Some error occurred"));
    }
    logi(("Leave from kernel"));
    return rc;
}
