#ifndef UTILS_H
#define UTILS_H

#include "stdio.h"

extern char *APP_NAME;

#define Dbg 0
#define Info 1
#define Err 2
#define Disable 4

#ifndef log_lvl
#define log_lvl Dbg
#endif

#if log_lvl == Dbg
#define log(lvl, msg) {printf(__FILE__":%d %s["lvl"]: ", __LINE__, APP_NAME); printf msg; puts("\n\r");}
#else
#define log(lvl, msg) {puts(APP_NAME); puts("["lvl"]: "); printf msg; puts("\n\r");}
#endif

#if Dbg >= log_lvl
#define logd(msg) log("Dbg ", msg)
#else
#define logd(msg)
#endif

#if Info >= log_lvl
#define logi(msg) log("Info", msg)
#else
#define logi(msg)
#endif

#if Err >= log_lvl
#define loge(msg) log("Err ", msg)
#else
#define loge(msg)
#endif

#define rci(cond, code, msg) if (cond) { loge(msg); return code; }
#define reci(cond, msg) rci(cond, -1, msg)

#endif // UTILS_H
