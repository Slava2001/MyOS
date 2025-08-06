#ifndef STDIO_H
#define STDIO_H

/**
 * Puts char on screen in current cursor position
 * @param c char to print
 */
void putc(char c);

/**
 * Puts null-terminated ascii string on screen in current cursor position
 * @param str poiner to null-terminated ascii string
 */
void puts(char *str);

/**
 * Clean screen
 * @param c char to print
 */
void clear_screen(void);

/**
 * Formatted output
 * @param fmt format string
 * @param ... args
 */
void printf(char *fmt, ...);

#endif // STDIO_H
