#include "index.h"
#include "stdbool.h"

void bubbleSort(int *array, int length){
    int a,b,t;

    for(int i = 0; i< length-1; i++){
        for(int j =0; j < length - 1; j++){
            if((a = array[j]) > (b= array[j+1])){
                t = a;
                array[j] = b;
                array[j+1] = t;
            }
        }
    }
}

void insertionSort(int *array, int length){
    int j,key,t;
    for(int i = 1; i< length; i++){
        j = i-1;
        key = array[i];
        while(j>=0 && array[j] > key){
            array[j+1] = array[j];
            j--;
        };
        array[j+1] = key;
    }
}

// Ogolnie to jest bubble sort ktory jak stwierdzi, ze nei posortowal niczego, to konczy funkcje, a nie leci dalej
void hybridBubbleSort(int *array,int length){
    int i, j,t;
    bool thereWasASwap;
    for (i = 0; i < length - 1; i++) {
        thereWasASwap = false;

        for (j = 0; j < length- i - 1; j++) {
            if (array[j] >array[j + 1]) {
                t=array[j];
                array[j] =array[j + 1];
                array[j + 1] =t;
                thereWasASwap = true;
            }
        }

        // Jezeli nie bylo swap'a, to tablica jest juz uporzadkowana
        if (thereWasASwap == false) break;
    }
}

void selectionSort(int *array,int length){
    int t;
    int indexOfMin,min;
    for(int i= 0;i<length-1;i++){
        indexOfMin=i;
        min = array[i];
        for(int j=i+1;j<length;j++){
            if((t = array[j]) < min){
                min = t;
                indexOfMin=j;
            }
        }
        if(indexOfMin != i){
            t = array[indexOfMin];
            array[indexOfMin] = array[i];
            array[i] = t;
        }
    }

}

void  binaryInsertionSort(int *array, int length){
    int left,right,middle;
    int value;

    for(int i = 1;i < length ; i++){
        value = array[i];
        left = 0;
        right = i-1;
        while(left <= right){
            middle = (left + right) / 2;
            if(value < array[middle]) right = middle - 1;
            else left = middle + 1;
        }
        for(int j = i-1;j>=left;j--) array[j+1] = array[j];
        array[left] = value;
    }
}

