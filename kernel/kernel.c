asm("jmp _main");
asm(".ascii \"main jmp\"");

#include "Types.h"
#include "stdio.h"


char now_dir_str[20]="A:";

void get_key_code();
void show_memory();

void main() {
	static char comand[20];

	clear_screen();
		
	printf("OS Started...\n\r");
	
    while(1)
	{
		printf("<Slava>: ");
		printf(now_dir_str);
		printf(">");

		scanf(comand,20);

		if(!strcmp(comand,"help")) {
			printf("   keycode\n\r   showmem\n\r");
		} else if(!strcmp(comand,"keycode")) {
			get_key_code();
		} else if(!strcmp(comand,"showmem")) {
			show_memory();
		} else {
			printf("Unknown command. Enter help.\n\r");
		}	
	}
}

void get_key_code()
{

	char a='\0';
	clear_screen();
	printf("Enter ESC to end");

	while(a!=27)
	{

	printf("\n\rcode of ");
	a=getc(true);


	printf(" :: ");
	printf(int2char(a));
	}

	clear_screen();
	return;
}

void show_memory()
{
char a='\0';
	int i=0;
	char * ptr=0x0;

	clear_screen();
	printf("Enter ESC to end. Use \'W\' and \'S\'\n\r");

	while(a!=27)
	{
		a=getc(false);
		if(a=='w'||a=='s')
		{
			if(a=='w'&& ptr>0)
				ptr-=32;

			printf(hex2char(ptr,2));
			printf(": ");

			for(i=0;i<16;i++)
			{
				printf(hex2char(*ptr,1));
				printf(" ");
				ptr++;
			}
				printf("    ");
				ptr-=16;
				for(i=0;i<16;i++)
				{
				if(*ptr>32)
					putc(*ptr);
				else
					putc('.');
				ptr++;
				}
			printf("\n\r");
		}
	}

	clear_screen();
	return;
}

// // void ShowDiskInfo()
// // {

	
// // 	printf("     DiskNum: ");
// // 	printf((HexChar(*PhysicalDiskNumber)));
// // 	printf("h\n\r");
	
	
// // 	printf("     BytesPerSector: ");
// // 	printf(HexChar(*BytesPerSector));
// // 	printf("h\n\r     SectorPerCluster: ");
// // 	printf(HexChar(*SectorPerCluster));
// // 	printf("h\n\r     ReservedSectors: ");
// // 	printf(HexChar(*ReservedSectors));
// // 	printf("h\n\r     NumberOfFATs: ");
// // 	printf(HexChar(*NumberOfFATs));
// // 	printf("h\n\r     RootEntries: ");
// // 	printf(HexChar(*RootEntries));
// // 	printf("h\n\r     TotalSectors: ");
// // 	printf(HexChar(*TotalSectors));
// // 	printf("h\n\r     MediaDescriptor: ");
// // 	printf(HexChar(*MediaDescriptor));
// // 	printf("h\n\r     SectorPerFat: ");
// // 	printf(HexChar(*SectorPerFat));
// // 	printf("h\n\r     SectorPerTrak: ");
// // 	printf(HexChar(*SectorPerTrak));
// // 	printf("h\n\r     Heads: ");
// // 	printf(HexChar(*Heads));
// // 	printf("h\n\r");
// // }

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

// // void Dir(char *baseptr, char *ptr)
// // {
	
// // int i=0;
// // int n=1;


// // loadSector((void *)baseptr,ptr);
		


// // while(*baseptr!=0)		
// // 	{
		

		
// // 		printf("     ");

		
// // 		for(i=0;i<8;i++)
// // 		putc(*(baseptr+i));
		 
// // 		if(*(baseptr+0x0b)==0x10)
// // 		{
// // 			printf(" DIR");
// // 		}else
// // 		{
// // 			putc('.');
// // 			for(;i<11;i++)
// // 			putc(*(baseptr+i));
// // 		}
		
// // 		printf("     ");
// // 		printf(HexChar(*(baseptr+i)));
// // 		printf("h\n\r");
// // 		baseptr+=32;
		
// // 		n++;
// // 		if(n==16)
// // 		{
// // 			if(getc()==27)
// // 			return;
// // 			n=0;
// // 			baseptr-=0x200;
// // 			ptr++;
// // 			loadSector(baseptr,ptr);
			
// // 		}
// // 	}
		
// // }

// // void loadSector(void * destptr,void * srcsektor)
// // {

// // 	void * destseg;
// // 	byte srchead;
// // 	byte srcsektr;
// // 	byte disknum=*PhysicalDiskNumber;
// // 	destseg=(int)destptr/16;
// // 	destptr=(int)destptr%16;

// // 	srchead=(int)srcsektor/(*SectorPerTrak);
// // 	srcsektr=(int)srcsektor%(*SectorPerTrak) +1;
	
	

// // //    /200 +1
// // 	__asm
// // 		{
// // 		mov   ax, destseg   ; сегмент куда пишем
// // 		mov   es, ax
// // 		mov	  bx, destptr    ; адрес куда пишем
// // 		mov   ch, 0			; дорожка 0
// // 		mov   cl, srcsektr   	; начиная с сектора 2
// // 		mov   dl, disknum      ; номер диска
// // 		mov   dh, srchead          ; номер головки
// // 		mov   ah, 2h        ; номер функции
// // 		mov   al, 1h
// // 		int   13h	
// // 		}
// // }


