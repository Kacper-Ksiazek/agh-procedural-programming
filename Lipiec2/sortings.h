#ifndef SORTINGS_H
#define SORTINGS_H

// 0. Zdefiniować typ wskaźnikowy na funkcje typu void z dwoma parametrami typu int* i int
typedef void (*pFun)(int*, int);

// 1. Sortowanie babelkowe
void bubbleSort(int *array, int length);
// 2. Mieszane sortowanie babelkowe
void hybridBubbleSort(int *array, int length);
// 3. Proste wstawianei
void insertionSort(int *array,int length);
// 4. Selection sort
void selectionSort(int *array,int length);
// 5. Połówkowe (zmodyfikowane proste wstawianie)
void binaryInsertionSort(int *array, int length);
// 6. HeapSort
// 7. Szybkie
void quickSort();

void printIntArray(int *array, int length);
#endif
