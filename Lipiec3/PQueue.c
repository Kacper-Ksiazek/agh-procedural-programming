#include "stdio.h"
#include "stdlib.h"

#include "ERROR_MESSAGES.h"
#include "tools.h"
#include "global.h"
#include "PQueue.h"

PQueue *PQCreate(int length) {
    PQueue* result = malloc(sizeof(PQueue));
    checkPointer(result, ERROR_MEMORY_ALLOCATION_QUEUE);

    // Dlugosc kolejki ustawiona jest na wartosc z argumentu
    result->nPQSize = length;
    result-> nPQCurrentSize = 0;

    // Alokujemy pamiec dla tablicy wskaznikow do struktur (dla naszej kolejki wlasciwej)
    result->pQueue = calloc(length,sizeof(PQItem*));
    checkPointer(result->pQueue,ERROR_MEMORY_ALLOCATION_PQINFO);

    return result;
}

int PQIsEmpty(PQueue *queue) {
    checkPointer(queue,ERROR_NULL_POINTER_QUEUE);

    if(queue->nPQCurrentSize == 0 ) return 1;
    else return 0;
}

int PQSize(PQueue *queue) {
    checkPointer(queue,ERROR_NULL_POINTER_QUEUE);

    return queue->nPQCurrentSize;
}

int PQMaxPrior(PQueue *queue) {
    if(PQIsEmpty(queue)) return PRIOR_ERROR;
    return queue->pQueue[0]->nPrior;
}


