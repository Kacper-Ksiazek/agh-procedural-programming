#include <time.h>
#include <stdio.h>

#include "Utils.h"

int getNumberFromUser(char* msg) {
	while (*msg) printf("%c", *msg++); // Wyswietlenie napisu

	int result;
	scanf_s("%d", &result);
	return result;
}

Range getRangeFromUser() {
	int min, max;
	while (1) {
		min = getNumberFromUser("Podaj wartosc minimalna: ");
		max = getNumberFromUser("Podaj wartosc maksymalna: ");

		if (min >= max) printf("\Wartosc minimalna musi byc MNIEJSZA niz maksymalna!!!\nSprobuj jeszcze raz\n\n");
		else break;
	}

	return (Range) { min, max };
}

int getRandomInt(Range* range) {
	return (rand() %
		(range->max - range->min + 1)) + range->min;
}

void insertionSort(int* array, int size) {
	int j, key;

	for (int i = 1; i < size; i++) {
		j = i - 1;
		key = array[i];
		while (j >= 0 && key < array[j]) {
			array[j + 1] = array[j];
			j -= 1;
		}
		array[j + 1] = key;
	}
}
