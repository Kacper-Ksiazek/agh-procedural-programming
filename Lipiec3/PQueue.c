#include "stdio.h"
#include "stdlib.h"

#include "tools.h"
#include "global.h"
#include "PQueue.h"

PQueue *PQCreate(int length) {
    PQueue* result = malloc(sizeof(PQueue));
    ensureProperMemoryAllocation(result);

    // Dlugosc kolejki ustawiona jest na wartosc z argumentu
    result->nPQSize = length;
    result-> nPQCurrentSize = 0;

    // Alokujemy pamiec dla tablicy wskaznikow do struktur (dla naszej kolejki wlasciwej)
    result->pQueue = calloc(length,sizeof(PQItem*));
    ensureProperMemoryAllocation(result->pQueue);

    return result;
}

int PQIsEmpty(PQueue *queue) {
    if(queue->nPQCurrentSize == 0 ) return 1;
    else return 0;
}

int PQSize(PQueue *queue) {
    return queue->nPQSize;
}

int PQMaxPrior(PQueue *queue) {
    if(PQIsEmpty(queue)) return PRIOR_ERROR;
    return queue->pQueue[0]->nPrior;
}


