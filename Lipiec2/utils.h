#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

typedef struct Range {
    int min;
    int max;
} Range;

Range *getRangeFromUser();
int getNumberFromUser(char *msg, bool negativeValues);
int randomIntFromRange(Range *range);
void printIntArray(int *array, int length);
void printTime(float deltaTime);
int *createArrayWithRandomValues(int size, Range *range);
int *cloneIntArray(const int *array, int size);


#endif
