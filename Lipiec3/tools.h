#pragma once

/**
 * Ensure that pointer is not equal to NULL
 *
 * @param p pointer; result of either **calloc** or **malloc**
 * @param msgOnError message that is going to be printed on error
 * @throw Error when memory has not been allocated properly
 */
void checkPointer(void *p, char *msgOnError);