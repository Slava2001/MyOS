#include "string.h"

// byte Strlen(
//         const char far* inStrSource 
//         )
// {
//         byte lenghtOfString = 0;
        
//         while(*inStrSource++ != '\0')
//         {
//             ++lenghtOfString;
//         }

//         return lenghtOfString;
// }

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


// char * IntChar(unsigned int a)
// {

// 	char *out="0000000000\0";
// 	char i=0;
		

// 	for(i=9;i>=-1;i--)
// 	{
// 	out[i]=(char)(a%10+48);
// 	a/=10;
// 	}
	

// 	for(i=0;i<9;i++)
// 		if(out[i]==48)out[i]=' ';else return (out+i);
	
// 	return out;
// }

// char * HexChar(unsigned int a)
// {
// 	char *out="0000000000\0";
// 	char i=0;
		
// 	for(i=9;i>=-1;i--)
// 	{
// 	if((a%16)<10)
// 		out[i]=(char)(a%16+48);
// 	else
// 		out[i]=(char)(a%16+55);
// 	a/=16;
// 	}
	
		
	
	
// 	for(i=0;i<9;i++)
// 		if(out[i]==48)out[i]=' ';else return (out+i);
	
// 	return out+i;
// }
// char * Hex2Char(byte a)
// {
// 	char *out="00\0";
// 	char i=0;
		
// 	for(i=1;i>=-1;i--)
// 	{
// 	if((a%16)<10)
// 		out[i]=(char)(a%16+48);
// 	else
// 		out[i]=(char)(a%16+55);
// 	a/=16;
// 	}
	
		
	
// 	return out;
// }

// int  strcpy(char* srs,char * des)
// {
// int i=0;

// for(;srs[i]!='\0';i++)
// 	des[i]=srs[i];

// 	return i;
// }
// int  stradd(char* srs,char * des)
// {
// int i=0;


// while(*des!='\0')
// des++;

// for(;srs[i]!='\0';i++)
// 	des[i]=srs[i];
// des[i]='\0';
// 	return i;
// }

// int  strdel(char * str,char stopchar)
// {
// int i;
// i=Strlen(str);

// for(;i>0&&str[i]!=stopchar;i--);

// 	str[i]='\0';

// 	return i;
// }








