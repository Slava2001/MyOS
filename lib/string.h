// CString.h 

#ifndef __STRING__
#define __STRING__

#include "Types.h"

 byte Strlen( const char far* inStrSource );
int strcmp(const char* a,const char *b);
char * Hex2Char(byte a);
char * HexChar(unsigned int a);
char * IntChar(unsigned long a);
int  strcpy(char* srs,char * des);
int  stradd(char* srs,char * des);
int  strdel(char * str,char stopchar);
#endif // __CSTRING__
