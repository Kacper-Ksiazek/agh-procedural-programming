#include "heap_sort.h"
#include "sortings.h"

void heaptify(int *array, int i, int length){
    int max_index = i;
    int left_index = 2 * i + 1;
    int right_index= 2 * i + 2;

    if(left_index < length && array[max_index] < array[left_index] ){
        max_index = left_index;
    }
    if(right_index < length && array[max_index] < array[right_index]){
        max_index = right_index;
    }

    if(max_index != i){
        int t = array[i];
        array[i] = array[max_index];
        array[max_index] = t;

        heaptify(array, max_index, length);
    }
}

void heapSort(int *array,int length){
    // Przygotowac heap'a
    for(int i = (length/2) -1;i>=0;i--){
        heaptify(array,i,length);
    }

    int t;
    for(int i = length-1; i >=0;i--){
        t = array[0];
        array[0] = array[i];
        array[i] = t;

        heaptify(array,0,length);
    }


    printIntArray(array,length);

    //
}