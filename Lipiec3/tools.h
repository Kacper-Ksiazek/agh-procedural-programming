#pragma once

/**
 * Ensure that pointer is not equal to NULL
 *
 * @param p pointer; result of either **calloc** or **malloc**
 * @param msgOnError message that is going to be printed on error
 * @throw Error when memory has not been allocated properly
 */
void checkPointer(void *p, char *msgOnError);


/**
 *
 * Generates a random number within a given range (boundary values included)
 *
 * @param min min value
 * @param max max value
 * @return random number within a range
 */
int getRandomNumberFromRange(int start, int stop);





