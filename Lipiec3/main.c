#include "stdio.h"
#include "stdlib.h"

#include "tools.h"
#include "PQueue.h"
#include "ERROR_MESSAGES.h"

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


/**
 * Allocate memory required for structure and returns pointer to it
 *
 * @param key value of nKey property
 * @param a value of nTab index 0
 * @param b value of nTab index 1
 * @return pointer to PQINFO structure
 */
PQINFO *createUserInfo(int key, int a, int b);


int main() {
    PQINFO *data1 = createUserInfo(1, 4, 5);
    PQINFO *data2 = createUserInfo(2, 5, 6);

//    printf("%d", compareTwoQueueElements(data1, data1));
//    printUserInfo(data);

    return 0;
}


void printUserInfo(const void *p) {
    // We have to assume that pointer is type of PQINFO
    const PQINFO *info = (PQINFO *) p;

    printf("   Klucz: %d\n", info->nKey);
    printf("   Tablica: [%d,%d]", info->pTab[0], info->pTab[1]);
}

PQINFO *createUserInfo(int key, int a, int b) {
    PQInfo *result = (PQINFO *) malloc(sizeof(PQINFO));
    checkPointer(result, ERROR_MEMORY_ALLOCATION_PQINFO);

    int *pTab = calloc(2, sizeof(int));
    checkPointer(result, ERROR_MEMORY_ALLOCATION_PTAB);

    pTab[0] = a;
    pTab[1] = b;

    result->nKey = key;
    result->pTab = pTab;

    return result;
};

void freeMemory(const void *p) {
    // We have to assume that pointer is type of PQINFO
    const PQINFO *info = (PQINFO *) p;

    free(info->pTab);
    free((void *) info);
    p = NULL;
}

int compareTwoQueueElements(const void *a, const void *b) {
    // We have to assume that both pointers are type of PQINFO
    const PQINFO *info1 = (PQINFO *) a;
    const PQINFO *info2 = (PQINFO *) b;

    if (info1->nKey != info2->nKey || info1->pTab[0] != info2->pTab[0] || info1->pTab[1] != info2->pTab[1]) return 0;
    return 1;
}
