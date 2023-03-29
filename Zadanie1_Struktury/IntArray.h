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

// 2.Funkcja tworz¹ca tablicê w strukturze;
IntArray create(int size);

// 3.Funkcja zwalniaj¹ca pamiêæprzydzielon¹ tablicy;
void deallocate(IntArray* array);
// 3.1
void allocate(IntArray* array);

// 4.Funkcja wype³niaj¹ca tablicê wartoœciami losowymi z podanego przez u¿ytkownika przedzia³u–jej argumentem ma byæ struktura, funkcja nic nie zwraca.

void fill(IntArray* array);

// 5.Funkcja sortuj¹ca tablicê–jej argumentem ma byæ struktura, funkcja nic nie zwraca.
void sort(IntArray* array);

// 6.Funkcja licz¹ca sumê wszystkich elementów–jej argumentem ma byæ struktura, funkcja zwraca obliczon¹ wartoœæ.
int sum(IntArray* array);

// UWAGA:
// Jest jakis konflikt nazw z "min" i "max", wiec sa takie inne

// 7.Funkcja znajduj¹ca najmniejszy element tablicy–jej argumentem ma byæ struktura, funkcja zwraca obliczon¹ wartoœæ.

int getMin(IntArray* array);

// 8.Funkcja znajduj¹ca najwiêkszy element tablicy–jej argumentem ma byæ struktura, funkcja zwraca obliczon¹ wartoœæ.

int getMax(IntArray* array);


#endif