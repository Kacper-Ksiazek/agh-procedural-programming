#pragma once
#include "global.h"

// 1. Constants

#define PRIOR_ERROR 1
#define POS_ERROR (-1)

// -------------

// 2. Structures

typedef struct PQItem{
    /** Priority of the element */
    int nPrior;
    /** Queue element's value */
    PQINFO *pInfo;
} PQItem;

typedef struct PQueue {
    /** pointer to the array of pointers to user info (array of user info) */
    PQItem **pQueue;
    /** Queue's maximum size */
    int nPQSize;
    /** Queue's current size */
    int nPQCurrentSize;
} PQueue;


// -------------

// 3. Queue functions

/**
 * Creates a new priority queue
 *
 * @param length maximum amount of elements in queue
 * @throw Error when memory could not be allocated properly
 * @return pointer to created queue
 */
PQueue* PQCreate(int length);


/**
 * Check whether a given queue is empty
 *
 * @param queue pointer to the queue
 * @return 1 when queue is empty and 0 otherwise
 */
int PQIsEmpty(PQueue *queue);


/**
 * Returns a number of elements currently in queue
 *
 * @param queue pointer to the queue
 * @return number of elements currently in queue
 */
int PQSize(PQueue *queue);


/**
 * Return the highest current priority
 *
 * @param queue pointer to the queue
 * @return either the highest current priority or PRIOR_ERROR when the queue is empty
 */
int PQMaxPrior(PQueue *queue);


/**
 * Insert a value into the queue with respect to its priority
 *
 * @param queue pointer to the queue
 * @param priority priority of an entry
 * @param data data to be added
 * @return 1 when data has added successfully or 0 otherwise
 */
int PQEnqueue(PQueue *queue, int priority, PQINFO *data);


/**
 * Get element with the highest priority and subsequently remove it from the queue
 *
 * @param queue pointer to the queue
 * @return either pointer to the element with the highest priority or NULL, when the queue is empty
 */
PQINFO *PQDequeue(PQueue *queue);


/**
 * Release entire memory allocated for all of queue's elements
 *
 * @param queue pointer to the queue
 * @param freeMemory pointer to the function which is responsible for releasing a memory
 *                   occupied by one queue's element
 */
void PQClear(PQueue *queue, void *freeMemory(const void *p));


/**
 * Release entire memory allocated for queue along with memory allocated for all of its elements;
 * converts pointer to the queue to the NULL pointer
 *
 * @param queue pointer to the queue
 * @param freeMemory pointer to the function which is responsible for releasing a memory
 *                   occupied by one queue's element
 */
void PQRelease(PQueue *queue, void *freeMemory(const void *p));


/**
 * Recursively print an entire queue, starting with given index
 *
 * @param queue pointer to the queue
 * @param printUserInfo pointer to the function which prints single user info
 * @param index index of element to start printing on
 */
void PQPrint(PQueue *queue, void *printUserInfo(const void *p), int index);


/**
 * Set a priority of particular queue element
 *
 * @param queue pointer to the queue
 * @param priority priority to be set
 * @param info queue element with priority to change
 * @param compareTwoQueueElements pointer to the function which compares two queue elements
 * @return either previous priority or PRIOR_ERROR when there is no such info element in the queue
 */
int PQSetPrior(PQueue *queue, int priority, PQInfo *info, int *compareTwoQueueElements(const void *a, const void *b));


/**
 * Set a priority of element on particular index
 *
 * @param queue pointer to the queue
 * @param priority priority to be set
 * @param index index of element with priority to change
 * @return either previous priority or PRIOR_ERROR when there is no info element with such index in the queue
 */
int PQsetPrior(PQueue *queue, int priority, int index);


/**
 * Get a priority of particular queue element
 *
 * @param queue pointer to the queue
 * @param info queue element whose priority we want to get
 * @param compareTwoQueueElements pointer to the function which compares two queue elements
 * @return either previous priority or PRIOR_ERROR when there is no such info element in the queue
 */
int PQGetPrior(PQueue *queue, PQInfo *info, int *compareTwoQueueElements(const void *a, const void *b));


/**
 * Set a priority of element on particular index
 *
 * @param queue pointer to the queue
 * @param index index of element element whose priority we want to get
 * @return either previous priority or PRIOR_ERROR when there is no info element with such index in the queue
 */
int PQgetPrior(PQueue *queue, int priority, int index);


/**
 * Find a index of particular user info
 *
 * @param queue pointer to the queue
 * @param info queue element whose index we want to get
 * @param compareTwoQueueElements pointer to the function which compares two queue elements
 * @return either user info's index or POS_ERROR when such element is not present in the queue
 */
int PQFind(PQueue *queue, PQInfo *info, int *compareTwoQueueElements(const void *a, const void *b));


// -------------

// 4. Static utility functions

/**
 * Restore heap via comparing nodes with its children and performing swaps if necessary (two comparison per iteration)
 *
 * @param arrayOfPQInfo pointer to the array of pointers to user info
 * @param start left index
 * @param stop right index
 */
static void UpdateDown(PQItem **arrayOfPQInfo, int start, int stop);


/**
 * Restore heap via comparing children with corresponding parent and performing swaps if necessary (one comparison per iteration)
 *
 * @param arrayOfPQInfo pointer to the array of pointers to user info
 * @param start left index
 * @param stop right index
 */
static void UpdateUp(PQItem **arrayOfPQInfo, int start, int stop);