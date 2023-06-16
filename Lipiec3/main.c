#include <stdio.h>
#include "PQueue.h"

/**
 * Print single user info struct
 *
 * @param p pointer to user info
 */
void printUserInfo(const void *p);


/**
 * Compare two queue elements
 *
 * @param a pointer to user info
 * @param b pointer to user info
 * @return 1 if they match, 0 otherwise
 */
int compareTwoQueueElements(const void *a, const void *b);


/**
 * Free memory allocated for single user info
 *
 * @param p pointer to user info
 */
void freeMemory(const void *p);


int main() {
    printf("Hello, World %d!\n", POS_ERROR);
    return 0;
}
