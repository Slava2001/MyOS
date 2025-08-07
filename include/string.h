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
 * Check if provided char id digit '0'-'9'
 * @param ch char  to check
 * @return true if ch is digit, else false
 */
int isdigit(char ch);
#endif // STRING_H
