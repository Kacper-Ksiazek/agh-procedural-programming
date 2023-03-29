#include <stdbool.h>

#ifndef _INTARRAY

typedef struct IntArray {
	const int length;
	int* values;

	bool _isSorted;
	bool _isFilled;
	bool _isAllocated;
} IntArray;


void printIntArray(IntArray* array);

// 2.Funkcja tworz�ca tablic� w strukturze;
IntArray create(int size);

// 3.Funkcja zwalniaj�ca pami��przydzielon� tablicy;
void deallocate(IntArray* array);
// 3.1
void allocate(IntArray* array);

// 4.Funkcja wype�niaj�ca tablic� warto�ciami losowymi z podanego przez u�ytkownika przedzia�u�jej argumentem ma by� struktura, funkcja nic nie zwraca.

void fill(IntArray* array);

// 5.Funkcja sortuj�ca tablic�jej argumentem ma by� struktura, funkcja nic nie zwraca.
void sort(IntArray* array);

// 6.Funkcja licz�ca sum� wszystkich element�w�jej argumentem ma by� struktura, funkcja zwraca obliczon� warto��.
int sum(IntArray* array);

// UWAGA:
// Jest jakis konflikt nazw z "min" i "max", wiec sa takie inne

// 7.Funkcja znajduj�ca najmniejszy element tablicy�jej argumentem ma by� struktura, funkcja zwraca obliczon� warto��.

int getMin(IntArray* array);

// 8.Funkcja znajduj�ca najwi�kszy element tablicy�jej argumentem ma by� struktura, funkcja zwraca obliczon� warto��.

int getMax(IntArray* array);


#endif