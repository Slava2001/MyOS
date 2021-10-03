#define NULL 0

#ifdef CRUTCH
void show_memory_map();
void *reserv_block(word start,word end);
void *malloc(word size);
void free(word start);
void init_disk();
void show_disk_info();
#endif


