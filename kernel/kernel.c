asm("jmp _main");
asm(".ascii \"main jmp\"");

#include "types.h"
#include "stdio.h"
#include "memmory.h"
// #include "fat.h"
// #include "graphic.h"
extern char *logo;

char now_dir_str[20]="A:";

void get_key_code();

void main() {
	static char comand[20];

	clear_screen();

	init_disk();
	// init_fat();
	
	printf(logo);
	printf("Press any key....");
	getc(false);
	clear_screen();
	printf("OS Started...\n\r");

    while(1)
	{
		printf("<Slava>: ");
		printf(now_dir_str);
		printf(">");

		scanf(comand,20);

		if(!strcmp(comand,"help")) {
			printf("   keycode\n\r   showmem\n\r   memmap\n\r   diskinfo\n\r   fatinfo\n\r   dir\n\r");
		} else if(!strcmp(comand,"keycode")) {
			get_key_code();
		} else if(!strcmp(comand,"showmem")) {
			show_memory();
		} else if(!strcmp(comand,"diskinfo")) {
			show_disk_info();
		//} else if(!strcmp(comand,"fatinfo")) {
			//show_fat_info();
		} else if(!strcmp(comand,"memmap")) {
			show_memory_map();
		//{ else if(!strcmp(comand,"dir")) {
			//show_current_dir();
		} else {
			printf("Unknown command. Enter help.\n\r");
		}	
	}
}

void get_key_code() {
	char a='\0';
	clear_screen();
	printf("Enter ESC to end");

	while(a!=27) {
		printf("\n\rcode of ");
		a=getc(true);
		printf(" :: ");
		printf(int2char(a));
	}

	clear_screen();
	return;
}

char *logo =
"                                                                               \n\r\
                                          @@@@                                 \n\r\
                         /-         @@@@@@@@@@@@                               \n\r\
                          @@@    @@@@@@@@@@@@@*@@@@                            \n\r\
                          @@@@@@@@@@@@@@@@@@@@**@@@@@@                         \n\r\
                         /-       @@@@@@@@@@@@@@@@                             \n\r\
                                  / //    /                                    \n\r\
                                                ###   ####                     \n\r\
                        ##   #  #  #  #  #  #  #   # #                         \n\r\
                       #  #  ###   #  #  ## #  #   #  ###                      \n\r\
                       #  #  ###   #  #  # ##  #   #     #                     \n\r\
                        ##   #  #   ##   #  #   ###  ####                      \n\r\
                                                                               \n\r";
