#include "stdio.h"
#include "stdlib.h"

#include "ERROR_MESSAGES.h"
#include "tools.h"
#include "global.h"
#include "PQueue.h"

PQueue *PQCreate(int length) {
    PQueue* result = malloc(sizeof(PQueue));
    checkPointer(result, ERROR_MEMORY_ALLOCATION_QUEUE);

    result->nPQSize = length;
    result-> nPQCurrentSize = 0;

    result->pQueue = calloc(length,sizeof(PQItem*));
    checkPointer(result->pQueue,ERROR_MEMORY_ALLOCATION_PQINFO);

    // In order to avoid conflicts with 0 instead of NULL pointers, assign a custom default value to all elements in queue
    for(int i=0; i<length;i++) result->pQueue[i] = NULL;

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

static void UpdateDown(PQItem **arrayOfPQItems, int start, int stop) {
    checkPointer(arrayOfPQItems,ERROR_NULL_POINTER_PQITEM_ARRAY);

    PQItem *temp; // In order to swap two elements
    int index = start;
    unsigned short leftChildIndex, rightChildIndex,highestPriorityElementIndex;

    while(1){
        leftChildIndex = index * 2 +1;
        rightChildIndex = index * 2 + 2;
        highestPriorityElementIndex= index;

        // Check if the priority of left side child is higher
        if(leftChildIndex <= stop && arrayOfPQItems[highestPriorityElementIndex]->nPrior < arrayOfPQItems[leftChildIndex]->nPrior){
            highestPriorityElementIndex= leftChildIndex;
        }
        // Check if the priority of right side child is EVEN higher
        if(rightChildIndex <= stop && arrayOfPQItems[highestPriorityElementIndex]->nPrior < arrayOfPQItems[rightChildIndex]->nPrior){
            highestPriorityElementIndex = rightChildIndex;
        }

        // Swap child with parent if they have higher priority
        if(highestPriorityElementIndex != index){
           temp = arrayOfPQItems[highestPriorityElementIndex];
           arrayOfPQItems[highestPriorityElementIndex] = arrayOfPQItems[index];
           arrayOfPQItems[index]= temp;
        }
        // Otherwise we are done, because the highest priority element has been on the top already
        else break;
    }
}

static void UpdateUp(PQItem **arrayOfPQItems, int start, int stop) {
    checkPointer(arrayOfPQItems,ERROR_NULL_POINTER_PQITEM_ARRAY );

    PQItem *temp; // In order to swap two elements
    int currentIndex= stop;
    unsigned short parentIndex;

    while( currentIndex>= start){
       parentIndex = ( currentIndex- 1) / 2;

       // If parent has smaller priority than element at currentIndex, then swap them
       if(arrayOfPQItems[parentIndex]->nPrior < arrayOfPQItems[currentIndex]->nPrior){
            temp= arrayOfPQItems[parentIndex];
            arrayOfPQItems[parentIndex] = arrayOfPQItems[currentIndex];
            arrayOfPQItems[currentIndex] = temp;

            currentIndex = parentIndex;
       }
       // Otherwise we're done, because chunk above is already sorted
       else break;
    }
}

int PQFind(PQueue *queue, PQInfo *info, int (*compareTwoUserInfo)(const void *a, const void *b)) {
    checkPointer(queue,ERROR_NULL_POINTER_QUEUE);
    checkPointer(info,ERROR_NULL_POINTER_PQINFO);
    checkPointer(compareTwoUserInfo,ERROR_NULL_POINTER_COMPARE_FN);

    for(int index = 0; index < queue->nPQCurrentSize; index++){
        if(compareTwoUserInfo(info,queue->pQueue[index]->pInfo) == 1) {
            return index;
        }
    }

    return POS_ERROR;
}

int PQEnqueue(PQueue *queue, int priority, PQINFO *data) {
    checkPointer(queue,ERROR_NULL_POINTER_QUEUE);
    checkPointer(data,ERROR_NULL_POINTER_PQINFO);

    // Ensure there is a space for one more entry
    if(PQSize(queue) == queue->nPQSize){
        // Throw an error via NULL pointer
        checkPointer(NULL, ERROR_QUEUE_CAPACITY_EXCEEDED);
        return 0;
    }

    // Create a new queue element
    PQItem *element= (PQItem *) malloc(sizeof(PQItem));
    checkPointer(element,ERROR_MEMORY_ALLOCATION_PQITEM);

    // Assign values
    element->nPrior = priority;
    element->pInfo = data;

    // Add element to queue
    int previousSize = PQSize(queue);
    queue->pQueue[previousSize] = element;
    queue->nPQCurrentSize++;

    // Reorder queue
    UpdateUp(queue->pQueue,0,previousSize);

    return 1;
}

PQINFO *PQDequeue(PQueue *queue) {
    checkPointer(queue, ERROR_MEMORY_ALLOCATION_QUEUE);

    if(PQIsEmpty(queue) == 1) return NULL;

    // Replace first queue element with the last one
    PQINFO *deletedElement = queue->pQueue[0]->pInfo;

    // Pre-decrement current queue size and assign its new value to the variable newSize
    int newSize = --(queue->nPQCurrentSize);

    // If the queue has become empty
    if(newSize == 0) {
        // then simply delete first (which is also the last) element of it
        queue->pQueue[0] = NULL;
    }
    else {
        // move the last element to the first (0 index) position
        queue->pQueue[0] = queue->pQueue[newSize];
    }

    // Reorder queue
    UpdateDown(queue->pQueue,0,newSize-1);

    return deletedElement;
}

void PQClear(PQueue *queue, void (*freeMemory)(const void *)) {
    checkPointer(queue,ERROR_NULL_POINTER_QUEUE);
    checkPointer(freeMemory,ERROR_NULL_POINTER_FREEMEMORY_FN);

    if(PQIsEmpty(queue)){
        printf("Kolejka juz jest pusta");
        return;
    }

    PQItem *item;
    for(int i = 0 ; i<queue->nPQCurrentSize;i++){
        item = queue->pQueue[i];
        // Free memory allocated for PQINFO
        freeMemory(item->pInfo);

        // Free memory allocated for PQItem
        free(item);

        queue->pQueue[i]= NULL;
    }

    queue->nPQCurrentSize=0;
}

void PQRelease(PQueue *queue, void (*freeMemory)(const void *)) {
    checkPointer(queue,ERROR_NULL_POINTER_QUEUE);
    checkPointer(freeMemory,ERROR_NULL_POINTER_FREEMEMORY_FN);

    // Free entire memory taken by array of PQItems
    PQClear(queue,freeMemory);

    // Free memory taken by queue structure;
    free(queue);

    queue=NULL;
}

void PQPrint(PQueue *queue, void (*printUserInfo)(const void *), int index) {
    checkPointer(queue,ERROR_NULL_POINTER_QUEUE);
    checkPointer(printUserInfo,ERROR_NULL_POINTER_PRINT_FN);

    int queueSize = PQSize(queue);
    if(queueSize) return;

    PQItem *element = queue->pQueue[index];

    printf("Priorytet elementu: %d",element->nPrior);
    printUserInfo(element->pInfo);

    // Print children
    int leftSideChildIndex = index * 2 + 1;
    int rightSideChildIndex = index *2 + 2;

    if(leftSideChildIndex < queueSize) PQPrint(queue, printUserInfo,leftSideChildIndex);
    if(rightSideChildIndex < queueSize) PQPrint(queue,printUserInfo,rightSideChildIndex);
}

int PQSetPrior(PQueue *queue, int priority, PQInfo *info, int (*compareTwoUserInfo)(const void *, const void *)) {
    checkPointer(queue,ERROR_NULL_POINTER_QUEUE);
    checkPointer(info, ERROR_NULL_POINTER_PQINFO);
    checkPointer(compareTwoUserInfo,ERROR_NULL_POINTER_COMPARE_FN);

    // Find an index of given info in the queue
    int index = PQFind(queue,info,compareTwoUserInfo);

    if(index == POS_ERROR) return PRIOR_ERROR;

    return PQsetPrior(queue,priority,index);
}

int PQsetPrior(PQueue *queue, int priority, int index) {
    checkPointer(queue,ERROR_NULL_POINTER_QUEUE);

    // Ensure there is a queue item on given index
    PQItem *element = queue->pQueue[index];
    checkPointer(element, "Proba zamiany priorytetu elementu na nieistniejacym indexie");

    // Save previous value before updating it with new one
    int previousPriority = element->nPrior;
    element->nPrior = priority;

    // Reorder queue
    UpdateDown(queue->pQueue,0, PQSize(queue)-1);

    return previousPriority;
}





