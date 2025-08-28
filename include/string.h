#ifndef STRING_H
#define STRING_H

#include "types.h"

/**
 * Write long int it buffer as string
 * @param val value to write
 * @param[out] buff buffer to write
 * @param len buffer len
 * @param base value base to convert in string
 * @return pointer to element in provided buffer
 *         It is pointer to start on val nul-terminated string representation
 *         If return value == buf, the result may be cut off because it does not fit into the buffer
 */
char* ltoa(long val, char *buff, int len, int base);

/**
 * Write unsigned long int it buffer as string
 * @param val value to write
 * @param[out] buff buffer to write
 * @param len buffer len
 * @param base value base to convert in string
 * @return pointer to element in provided buffer
 *         It is pointer to start on val nul-terminated string representation
 *         If return value == buf, the result may be cut off because it does not fit into the buffer
 */
char* ultoa(ulong val, char *buff, int len, int base);

/**
 * Convert null-terminated string with hex value to ulong
 * @param[in] str string with hex value
 * @return 0 on error, value on Ok.
 */
ulong ahtoul(char *str);

/**
 * Check if provided char is hex digit
 * @param ch char to check
 * @return 0 if provided char is not a hex digit
 */
int ishex(char ch);

/**
 * Check if provided char id digit '0'-'9'
 * @param ch char  to check
 * @return true if ch is digit, else false
 */
int isdigit(char ch);

/**
 * Trim trailing space in null-terminated string.
 * "hello\x20\x20\x20\0" -> "hello\0\x20\x20\0"
 * @param[inout] str null-terminated sring to trim spaces
 */
void trim_trailing_spaces(char *str);

/**
 * Return null-terminated string length (without null)
 * strlen("hello") == 5
 * @param[in] str input string
 * @return str length without terminated null
 */
uint strlen(char *str);

/**
 * Compare 2 null-terminated string
 * @param a first string
 * @param b second string
 * @return -1 if a < b, 1 if a > b, 0 if a == b
 */
int strcmp(char *a, char *b);

/**
 * Copy len bytes from src to dst
 * @param[out] dst destination address
 * @param[in] src source addres
 * @param len bytes count
 */
void memcpy(void *dst, void *src, uint len);

/**
 * Copy len bytes from far src to dst
 * @param[out] dst destination address
 * @param[in] segment source segment
 * @param[in] offset source offset
 * @param len bytes count
 */
void memcpy_from_far(void *dst, uint src_segment, uint src_offset, uint len);

/**
 * Copy null-terminated string
 * @param[out] dst destination address
 * @param[in] segment source segment
 * @param[in] offset source offset
 */
void strcpy_from_far(char *dst, uint src_segment, uint src_offset);

/**
 * Check if char is printable
 * @param ch char to check
 * @return true if char is printable
 */
int isprint(char ch);

/**
 * Convert ASCII letters to uppercase
 * @param[inout] buff buffer with null-terminated string
 */
void uppercase(char *buff);

#endif // STRING_H
