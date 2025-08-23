#ifndef STDIO_H
#define STDIO_H

#include "types.h"

/**
 * Puts char on screen in current cursor position
 * @param c char to print
 */
void putc(char c);

/**
 * Get char form input
 * @return char
 */
char getc();

/**
 * Get null-terminated string
 * @param[out] buff to save stirng
 * @param buff_size buff size
 * @return sting len
 */
char gets(char *buff, uint buff_size);

#define KEY_ENTER     0x1C0D
#define KEY_BACKSPACE 0x0E08
#define KEY_ESC       0x011B

/**
 * Get keyboard key
 * @return ASCII char in low byte, scancode in highth
 */
uint get_key();

/**
 * Puts null-terminated ascii string on screen in current cursor position
 * @param str pointer to null-terminated ascii string
 */
void puts(char *str);

/**
 * Clean screen
 */
void clear_screen(void);

/**
 * Formatted output
 * @param fmt format string
 * @param ... args
 */
void printf(char *fmt, ...);

#endif // STDIO_H
