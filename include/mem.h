#define NULL 0

#ifdef CRUTCH
void show_memory_map();
void *reserv_block(word start,word end);
void *malloc(word size);
void free(word start);
void init_disk();
void show_disk_info();
void load_sector(word desk_ptr,word src_sector);
void show_memory();
#endif


