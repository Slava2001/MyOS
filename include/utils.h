#ifndef UTILS_H
#define UTILS_H

#include "stdio.h"

#if 0
#define log(lvl, msg) {printf(__FILE__":%d ["#lvl"]: ", __LINE__); printf msg; puts("\n\r");}
#else
#define log(lvl, msg) {puts("["#lvl"]: "); printf msg; puts("\n\r");}
#endif

#define logi(msg) log(Info, msg)
#define loge(msg) log(Err,  msg)
#define logd(msg) log(Dbg,  msg)

#define rci(cond, code, msg) if (cond) { loge(msg); return code; }
#define reci(cond, msg) rci(cond, -1, msg)

#endif // UTILS_H
