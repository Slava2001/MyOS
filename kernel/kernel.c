asm("jmp _main");
asm(".ascii \"main jmp\"");

#include "Types.h"
#include "stdio.h"


char NowDirS[20]="A:";





void main() {
	
	clear_screen();
		
	printf("OS Started...\n\rddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
	
	//char comand[20] = "";

    while(1)
	{
		//printf("<Slava>: ");
		// printf(NowDirS);
		// printf(">");
		
		

		//scanf(comand,20);
		
		//strcmp("12","12");
		//lolo();
		//if(!strcmp("help","help")) {
			//printf("   keycode\n\r   cd\n\r   showmem\n\r   diskinfo\n\r   dir\n\r   restart\n\r");
		//} //else {
		// 	printf("Error comand!!!\n\r");
		// }	
	}
}
int strcmp(a, b) char *a, *b;
{
	int i=0;
	int delta=0;
	
	while(a[i]!='\0' && b[i]!='\0')
	{
		delta=a[i]-b[i];
		if(delta!=0)return delta;
		i++;
	}
	delta=a[i]-b[i];
	return delta;
}


// // #include "string.h"

// // word *BytesPerSector;
// // byte *SectorPerCluster;
// // word *ReservedSectors;
// // byte *NumberOfFATs;
// // word *RootEntries;
// // word *TotalSectors;
// // byte *MediaDescriptor;
// // word *SectorPerFat;
// // word *SectorPerTrak;
// // word *Heads;
// // byte *PhysicalDiskNumber;
// // char *NowDir;
// // char NowDirS[20]="A:";


// // void cd();
// // void getKeyCode();
// // void ShowMemory();
// // void ShowDiskInfo();
// // void Dir(char *baseptr,char *ptr);
// // void loadSector(void *destptr,void *srcsektor);

// void BootMain()
// {

// 	// char comand[20];
// 	// BytesPerSector		=0x7c00+0x0b;
// 	// SectorPerCluster	=0x7c00+0x0d;
// 	// ReservedSectors		=0x7c00+0x0e;
// 	// NumberOfFATs		=0x7c00+0x10;
// 	// RootEntries			=0x7c00+0x11;
// 	// TotalSectors		=0x7c00+0x13;
// 	// MediaDescriptor		=0x7c00+0x15;
// 	// SectorPerFat		=0x7c00+0x16;
// 	// SectorPerTrak		=0x7c00+0x18;
// 	// Heads				=0x7c00+0x1a;
// 	// PhysicalDiskNumber	=0x7c00+0x24;
// 	// NowDir=*ReservedSectors+*SectorPerFat*(*NumberOfFATs);
	
//     // ClearScreen();
//     // ShowCursor(true);
	
	
// 	// printf("OS Started...\n\r");
	
	
	
	
	
//     while(1)
// 	{
// 	__asm__(".intel_syntax noprefix\n\t"
// 			"mov al, '>' \n\t"
// 			"mov ah, 0x0E \n\t"
// 			"mov bh, 0 \n\t"
// 			"int 0x10 \n\t");

// 		// printf("<Slava>: ");
// 		// printf(NowDirS);
// 		// printf(">");
		
// 		// scanf(comand,20);

// 		// if(!strcmp(comand,"help"))
// 		// 	printf("   keycode\n\r   cd\n\r   showmem\n\r   diskinfo\n\r   dir\n\r   restart\n\r");
// 		// else if(!strcmp(comand,"keycode"))
// 		// 	getKeyCode();
// 		// else if(!strcmp(comand,"showmem"))
// 		// 	ShowMemory();
// 		// else if(!strcmp(comand,"diskinfo"))
// 		// 	ShowDiskInfo();
// 		// else if(!strcmp(comand,"dir"))
// 		// 	Dir(0x3000,NowDir);
// 		// else if(!strcmp(comand,"cd"))
// 		// 	cd();
// 		// else if(!strcmp(comand,"restart"))
// 		// 	break;
// 		// else
// 		// 	printf("Error comand!!!\n\r");
	
	
// 	}

//     return;
// }


// // void getKeyCode()
// // {

// // 	char a='\0';
// // 	ClearScreen();
// // 	printf("Enter ESC to end");

// // 	while(a!=27)
// // 	{

// // 	printf("\n\rcode of ");
// // 	a=getc();


// // 	printf(" :: ");
// // 	printf(IntChar(a));
// // 	}

// // 	ClearScreen();
// // 	return;
// // }

// // void ShowMemory()
// // {
// // char a='\0';
// // 	int i=0;
// // 	char far* ptr=0x3000;

// // 	ClearScreen();
// // 	printf("Enter ESC to end. Use \'W\' and \'S\'\n\r");

// // 	while(a!=27)
// // 	{
// // 		a=getc(false);
// // 		if(a=='w'||a=='s')
// // 		{
// // 			if(a=='w'&& ptr>0)
// // 				ptr-=32;




// // 			printf(HexChar(ptr));
// // 			printf(": ");

// // 			for(i=0;i<16;i++)
// // 			{
// // 				printf(Hex2Char(*ptr));
// // 				printf(" ");
// // 				ptr++;
// // 			}
// // 				printf("    ");
// // 				ptr-=16;
// // 				for(i=0;i<16;i++)
// // 				{
// // 				if(*ptr>32)
// // 					putc(*ptr);
// // 				else
// // 					putc('.');
// // 				ptr++;
// // 				}
// // 			printf("\n\r");
// // 		}
// // 	}

// // 	ClearScreen();
// // 	return;
// // }
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


