#include "string.h"

int strcmp(char *a, char *b) {
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

char* int2char(int a) {
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

char* hex2char(unsigned int a, unsigned int l) {
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
