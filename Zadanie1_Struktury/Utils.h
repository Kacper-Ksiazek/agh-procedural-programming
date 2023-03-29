#ifndef _UTILS

typedef struct Range {
	int min;
	int max;
} Range;

Range getRangeFromUser();

int getRandomInt(Range* range);

void insertionSort(int* array);


#endif