#pragma once
#include "global.h"

// 1. Stale

#define PRIOR_ERROR 1         // Minimalna wartosc calkowita (byle co)
#define POS_ERROR (-1)        // Index jakiego nie ma

// -------------

// 2. Struktury

typedef struct PQItem{
    int nPrior;               // Priorytet
    PQINFO *pInfo;            // Wartosc elementu kolejki
} PQItem;

typedef struct PQueue {
    PQItem **pQueue;          // Wskaznik do kolejki (tablicy wskaznikow do struktur)
    int nPQSize;
    int nPQCurrentSize;
} PQueue;

// -------------

// 3. Funkcje stosu

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