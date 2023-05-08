#include "stdio.h"
#include "sortings.h"
#include "stdlib.h"
#include "heap_sort.h"

//Zadanie 2
//Porównanie sortowań:
//- bąbelkowe;
//- mieszane bąbęlkowe;
//- proste wstawianie;
//- proste wybieranie;
//- połówkowe (zmodyfikowane proste wstawianie);
//- HeapSort (stogowe z funkcją update(), która przywraca warunek stogu);
//- szybkie;
//Rozmiar tablicy dynamicznej (zwalnianie pamięci!) tworzony w main. Zdefiniować typ wskaźnikowy na funkcje typu void z dwoma parametrami typu int* i int
//        i zdefiniować tablicę adresów(nazw funkcji) sortujących i tablicę const char* zaweirającą nazwy sortowań - obie deklarowane bezrozmiarowo - rozmiar na podstawie inicjacji tablicy;
//Pętla testująca sortowania działa tyle razy ile sizeof(SortFun)/sizeof(pFun) gdzie SortFun to tablica z adresami, a pFun, to typ elementu tej tablicy.
//Ważne, żeby sortowania były realizowane na identycznie zainicjowanej tablicy Po alokacji.
//
int randomIntFromRange(int min, int max){
    // Na to jest wzor po prostu, bez filozofii
    return (rand() % (max - min + 1)) + min;
}

int *createArrayWithRandomValues(int size, int min, int max){
    int *p = (int *) calloc(size,sizeof(int));
    // Sprawdzamy, czy udalo sie utworzyc tablice
    if( p == NULL){
        printf("nie udalo sie zaalokowac pamieci wymaganej do prawidlowego utworzenia tablicy!");
        exit(1);
    }
    // Wypelniamy ja losowymi wartosciami
    int i= 0;
    while (i!=size) p[i++] = randomIntFromRange(min, max);
    //
    return p;
}

int main(){
    const int ARRAY_LENGTH = 9;
    int *p = createArrayWithRandomValues(ARRAY_LENGTH, -11,10);

    pFun function[] = {&bubbleSort,&insertionSort,&hybridBubbleSort, &selectionSort};
    char* names[]={"Bubble sort", "Insertion sort", "Hybrid Bubble sort", "Selection sort"};

    printIntArray(p, ARRAY_LENGTH);
    printf("\n");

    heapSort(p,ARRAY_LENGTH);

//    printf("\n");
////    insertionSort(p,ARRAY_LENGTH);
//    printf("\n");
////    bubbleSort(p,ARRAY_LENGTH);
//    binaryInsertionSort(p,ARRAY_LENGTH);
//
//    printf("\n");
//    printIntArray(p, ARRAY_LENGTH);

    return 0;
}