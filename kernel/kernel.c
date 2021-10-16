asm("jmp _main");
asm(".ascii \"main jmp\"");

#include "Types.h"
#include "stdio.h"
#include "mem.h"
#include "fat.h"
#include "graphic.h"
#include "logo.h"

char now_dir_str[20]="A:";

void get_key_code();
void show_memory();

void main() {
	static char comand[20];

	clear_screen();

	init_disk();
	init_fat();
	
	printf(logo);
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
		} else if(!strcmp(comand,"fatinfo")) {
			show_fat_info();
		} else if(!strcmp(comand,"memmap")) {
			show_memory_map();
		} else if(!strcmp(comand,"dir")) {
			show_current_dir();
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

// // void cd()
// // {
// // char * baseptr=0x3000;
// // char * ptr=NowDir;
// // char ndir[9];
// // int i=0;
// // int n=1;
// // int ndirlen=0;

// // i=scanf(ndir,9);
// // ndirlen=i;

// // for(;i<8;i++)
// // 	ndir[i]=0x20;
// // ndir[8]='\0';


// // loadSector((void *)baseptr,ptr);
// // while(*baseptr!=0)		
// // 	{
		
// // 		if(*(baseptr+0x0b)==0x10)
// // 		{
// // 			if(*(ndir+0)==*(baseptr+0))
// // 			if(*(ndir+1)==*(baseptr+1))
// // 			if(*(ndir+2)==*(baseptr+2))
// // 			if(*(ndir+3)==*(baseptr+3))
// // 			if(*(ndir+4)==*(baseptr+4))
// // 			if(*(ndir+5)==*(baseptr+5))
// // 			if(*(ndir+6)==*(baseptr+6))
// // 			if(*(ndir+7)==*(baseptr+7))	
// // 			{
				
// // 				NowDir=(*ReservedSectors)+(*SectorPerFat)*(*NumberOfFATs);
// // 				if(*(baseptr+0x1a)>0){
// // 				NowDir+=((*RootEntries)*32)/(*BytesPerSector);	
// // 				NowDir+=(*(baseptr+0x1a)-2)*(*SectorPerCluster);
// // 				}
				
// // 				if(!strcmp(ndir,"..      "))
// // 				{
// // 					strdel(NowDirS,'\\');
// // 				}
// // 				else
// // 				{
// // 					stradd("\\",NowDirS);
// // 					ndir[ndirlen]='\0';
// // 					stradd(ndir,NowDirS);
// // 				}
			
				
// // 				return;
// // 			}
// // 		}
// // 		n++;
// // 		baseptr+=32;
// // 		if(n==16)
// // 		{
// // 			n=0;
// // 			baseptr -= 0x200;
// // 			ptr++;
// // 			loadSector(baseptr,ptr);
// // 		}
// // 	}
	
// // 	printf("Folder not found!\n\r");
	
// // }
