#ifndef UTILS_H
#define UTILS_H

#include "stdio.h"

extern char *APP_NAME;

#if 0
#define log(lvl, msg) {printf(__FILE__":%d %s["#lvl"]: ", __LINE__, APP_NAME); printf msg; puts("\n\r");}
#else
#define log(lvl, msg) {puts(APP_NAME); puts("["#lvl"]: "); printf msg; puts("\n\r");}
#endif

#define logi(msg) log(Info, msg)
#define loge(msg) log(Err,  msg)
#ifdef DEBUG
#define logd(msg) log(Dbg,  msg)
#else
#define logd(msg)
#endif

#define rci(cond, code, msg) if (cond) { loge(msg); return code; }
#define reci(cond, msg) rci(cond, -1, msg)

#endif // UTILS_H
