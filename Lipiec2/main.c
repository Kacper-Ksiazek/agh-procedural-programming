#include "stdio.h"
#include "time.h"
#include "utils.h"
#include "sortings/index.h"

typedef void (*pFun)(int*, int);

typedef struct FunctionWithLabel{
    char* label;
    pFun fn;
} FunctionWithLabel;


int main(){
    printf("PROJEKT 2: Porownanie sortowan\n\nParametry generowanej tablicy: \n");
    const int arrayLength= getNumberFromUser("  -Ilosc elementow w tablicy: ", false);
    Range *range = getRangeFromUser();

    const int *originalArrayPointer = createArrayWithRandomValues(arrayLength, range);

//    printf("\nWygenerowana tablica: \n");
//    printIntArray((int*) originalArrayPointer,arrayLength);

    const FunctionWithLabel functions[]= {
            {"Babelkowe (bubbleSort)", &bubbleSort},
            {"Mieszane babelkowe (hybridBubbleSort)", &hybridBubbleSort},
            {"Proste wstawianie (insertionSort)", &insertionSort},
            {"Proste wybieranie (selectionSort", &selectionSort },
            {"Polowkowe; zmodyfikowane proste wstawianie (binaryInsertionSort)", &binaryInsertionSort},
            {"HeapSort", &heapSort},
            {"Szybkie (quickSort)", &quickSort}
    };

    const unsigned short amountOfSortingFunctions = sizeof(functions)/ sizeof(FunctionWithLabel);

    printf("\nPorownanie czasu sortowan:\n");

    for(int i = 0; i< amountOfSortingFunctions;i++ ){
        printf("%d- %s\n", i+1,functions[i].label);
        int *array = cloneIntArray(originalArrayPointer,arrayLength);

        clock_t start,end;
        start = clock();

        functions[i].fn(array,arrayLength);

        end = clock();

        // Roznica czasu pomiedzy startem i koncem wyrazona w sekundach
        const float deltaTime =  ( (float)(end - start) / CLOCKS_PER_SEC );

        printf("   Czas: ");
        printTime(deltaTime);
    }
    return 0;
}