#ifndef FCALL_H
#define FCALL_H

/**
 * Call `int fn()` function.
 * @param segment function segment
 * @param offset function offset
 * @return called function return code
 */
int fcall(uint segment, uint offset);

#endif // FCALL_H
