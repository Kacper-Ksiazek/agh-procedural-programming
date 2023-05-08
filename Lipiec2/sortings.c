#include "sortings.h"
#include "stdio.h"

void bubbleSort(int *array, int length){
    printf("Bubble sort: ");
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

    printIntArray(array,length);
}

void insertionSort(int *array, int length){
    printf("\nInsertion sort: ");

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

    printIntArray(array,length);
}

// Hybrid bubble sort = bubble sort + insertion sort
void hybridBubbleSort(int *array,int length){
    int a,b,t; // Do bubble sorta
    int j, indexOfLastSwappedElement; // Do insertion sorta

    for(int i =0;i<length-1;i++){
        indexOfLastSwappedElement=-1;
        // Robimy jedna ture bubble sorta
        // int j nie jest potrzebne, bo j juz jest zadeklarowane
        for(j =0;j<length-1;j++){
            if((a = array[j]) > (b= array[j+1])){
                t = a;
                array[j] = b;
                array[j+1] = t;
                indexOfLastSwappedElement=j;
            }
        }
        // Jezeli bubble sort niczego nie posortowal albo jezeli posortowal jedynie pierwszy element,
        // to znaczy, ze tablica jest gotowa
        if(indexOfLastSwappedElement==-1 || indexOfLastSwappedElement == 0) return;
        // W przeciwnym razie robimy insertion sorta
        j = indexOfLastSwappedElement - 1;
        t = array[indexOfLastSwappedElement];
        while(j>=0 && array[j] > t){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = t;
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

void printIntArray(int *array, int length){
    int i =0;
    printf("[");
    while(i < length){
        printf("%d%s", array[i], i == length-1 ? "\0" : ", ");
        i++;
    }
    printf("]");
}
