#include "quick_sort.h"

void quickSort(int *array, int length) {
    recursiveQuickSort(array,0,length-1);
}

void recursiveQuickSort(int *array, int left, int right){
    // Jako ze jest to funkcja rekurencyjna, potrzebujemy warunku
    // chroniacego przed wywolywaniem jej w nieskonczonosc
    if(left < right){
        // Okreslamy srodkowy element (konwencjonalnie pierwszy element od prawej strony)
        int pivot = array[right];
        int indexOfLastElementSmallerThanPivot = left -1; // bo na poczatku nie ma niczego mniejszego
        int t; // to do swapowania potrzebne

        for(int j = left;j<right;j++){
            if(array[j] < pivot){
                indexOfLastElementSmallerThanPivot++;
                t = array[j];
                array[j] = array[indexOfLastElementSmallerThanPivot];
                array[indexOfLastElementSmallerThanPivot] = t;
            }
        }
        // Na koncu wstawiamy pivota w odpowiednie miejsce
        t = array[right];
        array[right] = array[indexOfLastElementSmallerThanPivot + 1];
        array[indexOfLastElementSmallerThanPivot + 1] = t;

        // Teraz nasz element pivot jest na odpowiednim miejscu w tablicy
        // Powtarzamy te sama procedure osobno dla prawej i lewej strony od pivota
        recursiveQuickSort(array, left,indexOfLastElementSmallerThanPivot);
        recursiveQuickSort(array, indexOfLastElementSmallerThanPivot + 2,right);
    }
}
