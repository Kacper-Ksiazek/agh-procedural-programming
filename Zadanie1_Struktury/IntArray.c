#include <stdio.h>
#include <stdlib.h>

#include "Utils.h"
#include "IntArray.h"

// 0.
void printIntArray(IntArray* array) {
	if (array->_isFilled == false) {
		printf("NIE MOZESZ WYSWIETLIC NIEWYPELNIONEJ TABLICY!!!");
		return;
	}

	int size = array->length;

	printf("[");
	for (int i = 0; i < size; i++) {
		printf((i == size - 1) ? "%d" : "%d, ", array->values[i]);
	}
	printf("]\n");
}

// 2.
IntArray create(int size) {
	IntArray result = {
		size,   // length
		NULL, // values
		false,  // _isSorted
		false,  // _isFilled
		false	// _isAllocated
	};

	allocate(&result);

	return result;
}

// 3.
void deallocate(IntArray* array) {
	if (array->_isAllocated == false) {
		printf("NIE MOZNA DEALOKOWAC UPRZEDNIO ZDEALOKOWANEJ TABLICY");
		return;
	}

	free(array->values);

	array->values = NULL;
	array->_isAllocated = false;
	array->_isFilled = false;
	array->_isSorted = false;

	printf("Tablica zostala zdealokowana pomyslnie");
}

// 3.1
void allocate(IntArray* array) {
	if (array->_isAllocated == true) {
		printf("NIE MOZNA ALOKOWAC UPRZEDNIO ZALOKOWANEJ TABLICY");
		return;
	}

	array->values = malloc(sizeof(int) * array->length);
	array->_isAllocated = true;
}

// 4.
void fill(IntArray* array) {
	if (array->_isAllocated == false) {
		printf("NIE MOZESZ WYPELNIC TABLICY BEZ ZAALOKOWANEJ PAMIECI!!!");
		return;
	}

	int size = array->length;

	printf("Wypelnianie tablicy\n");
	Range range = getRangeFromUser();

	for (int i = 0; i < size; i++) {
		array->values[i] = getRandomInt(&range);
	}

	array->_isFilled = true;
}

// 5.
void sort(IntArray* array) {
	if (array->_isFilled == false) {
		printf("NIE MOZNA SORTOWAC NIEWYPELNIONEJ TABLICY!!!");
		return;
	}

	insertionSort(array->values, array->length);
	array->_isSorted = true;
}

// 6.
int sum(IntArray* array) {
	int result = 0;
	for (int i = 0; i < array->length; i++) result += array->values[i];

	return result;
}

// 7.
int getMin(IntArray* array) {
	if (array->_isSorted == false) sort(&array);
	return array->values[0];
}

// 8.
int getMax(IntArray* array) {
	if (array->_isSorted == false) sort(&array);
	return array->values[array->length - 1];
}