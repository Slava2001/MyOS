#ifndef INCLUDE_STDIO_H
#define INCLUDE_STDIO_H

#define BLACK			0x0
#define BLUE			0x1
#define GREEN			0x2
#define CYAN			0x3
#define RED			0x4
#define MAGENTA			0x5
#define BROWN			0x6
#define GREY			0x7
#define DARK_GREY		0x8
#define LIGHT_BLUE		0x9
#define LIGHT_GREEN		0xA
#define LIGHT_CYAN		0xB
#define LIGHT_RED		0xC
#define LIGHT_MAGENTA           0xD
#define LIGHT_BROWN		0xE
#define WHITE			0xF

#include "Types.h"
#include "string.h"

#ifdef CRUTCH
void putc(int c);
void clear_screen();
void printf(char *str);
char getc(char out);
int scanf(char *ptr, char l);
#endif

#endif