#ifndef INCLUDE_MEMMORY_H
#define INCLUDE_MEMMORY_H

#include "types.h"

#define NULL 0

void show_memory_map();
void *reserv_block(word start, word end);
void *malloc(word size);
void free(word start);
void init_disk();
void show_disk_info();
void show_memory();

#endif // INCLUDE_MEMMORY_H