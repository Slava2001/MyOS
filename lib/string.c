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


char * int2char(a) int a;
{
	static char out[10] = "000000000";
	char i = 8;
    char sign = 0;
	if (a < 0) {
        sign = 1;
        a = -a;
    }

    do {
        int tmp = a / 10;  
        out[i] = a - tmp * 10 + '0';
        a = tmp;
        i--;
    } while (i > 0 && a > 0);
    if (sign) {
        out[i]='-';
        i--;
    }
	i++;
	return out + i;
}



char * hex2char(a,l) unsigned int a,l;
{
	static char out[10] = "000000000";
    char i = 8;
		
    for (; i > 0 && a > 0; i--) {  
        int tmp = a / 16;  
        out[i] = a - tmp * 16 + '0';
        if (out[i] > '9') {
            out[i] += 'A'-'9' - 1;
        }
        a = tmp;
    }
    for (;i > 0; i--) {
        out[i] = '0';
    }
	return out + 9 - l*2;

}

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








