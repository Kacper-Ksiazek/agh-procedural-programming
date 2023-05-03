#include "int_stack.h" // to jest do typow stosu
#include "stdlib.h" // to jest do calloca i malloca
#include "stdio.h" // printf, exit
#include "config.h" // do MAX_STACK_LENGTH

// Moje pomocnicze funkcje
int findLastElementIndex_int(IntStackItem **pStack){
    if(isEmpty_int(pStack)) return -1;
    int index = 0;
    while(pStack[index]->pNext !=NULL) index++;

    return index;
}

void throwError_int(char *functionName){
    fprintf(stderr, "Proba wywolania %s top_char na pustym zbiorze", functionName);
    exit(1);
}

IntStackItem** createIntStack(){
    // W typescript'cie to mozna robic za pomoca operatora "as"
    // Uzywajac okraglych nawiasow przed wyrazaniem ZMIENIAMY JEGO TYP
    // zarowno malloc jak i calloc defaultowo zwracaja "void*" a my chcemy "IntStackItem*"
    //
    IntStackItem** result = (IntStackItem**) calloc(MAX_STACK_LENGTH, sizeof(IntStackItem));
    // Musimy sprawdzic, czy udalo sie zaakalowac pamiec
    if(result == NULL){
        printf("Blad podczas tworzenia tablicy struktur!!!!");
        exit(1);
    }

    return result;
}

int isEmpty_int(IntStackItem** pStack){
    // Roznica pomiedzy callockiem a mallockiem jest taka, ze:
    // - uzywajac callocka: default'owa wartosc dla wszystkich elementow tablicy to 0
    // - uzywajac mallocka: brak default'owej wartosci, dlatego podczas
    //                      odwolywania sie do nieistniejacego indexu dzieja sie cuda
    if(pStack[0] == 0) return 1;
    return 0;
}

void push_int(IntStackItem** pStack, int x){
    // Musimy uzyc malloca, zeby ominac gargabe collector kompilatora C
    // garbage collector to taki mechanizm, ktory sprzata (kasuje) zmienne po zakonczeniu wykonywania funkcji
    // a my nie chcemy, zeby nasza struktura przepadla, dlatego deklarujemy ja w taki sposob

    IntStackItem *freshElement = (IntStackItem*) malloc(sizeof(IntStackItem));
    freshElement->key = x;
    freshElement->pNext = NULL;

    if(isEmpty_int(pStack) == 1){
        pStack[0] = freshElement;
    } else {
        int length = 0;
        while(pStack[length++]->pNext != NULL);
        // Sprawdzamy, czy nie mamy za duzego stosu
        if(length >= MAX_STACK_LENGTH){
            // Jak mamy, to wyswietlamy komunikat o bledzie programu
            fprintf(stderr,"Maksymalny rozmiar stosu (%d) zostal przekroczony!!!",MAX_STACK_LENGTH );
            // Ta funkcja zamyka program z konkretnym kodem
            // Te kody to mozna olac raczej i pisac exit(1), bo kod 0 to brak bledu (dlatego sie pisze return 0)
            // Jak sie jest ambitnym to mozna sobie wygooglowac tabelke error code'ow dla jezyka C i szukac pasujacego
            // Inne tabelki bledow kodow to na przyklad HTTP Responses Status Codes

            exit(1);
        }

        // Przedostatni element stosu musi miec ustawiony adres nastepnego elementu na ten nasz nowy element
        pStack[length-1]->pNext = freshElement;
        // Dodatkowo adres nowego elementu umieszamy na koncu tablicy
        pStack[length] = freshElement;
    }

    // CLION mowi ze na koncu void'owej funkcji nie trzeba pisac return'a
}

int pop_int(IntStackItem** pStack){
    // Znajdujemy index ostatniego elementu
    int index = findLastElementIndex_int(pStack);

    // Sprawdzamy, czy stos nie jest pusty
    if(index == -1) throwError_int("pop_int");

    // Zapisujemy znak pod tym indexem
    int result = pStack[index]->key;

    // Uzywamy funkcji del_int do skasowania ostataniego elementu, jak i referencji do niego w przedostatnim elemencie
    del_int(pStack);

    // Zwracamy uprzednio zapisany element
    return result;
}

int top_int(IntStackItem **pStack){
    // Znajdujemy index ostatniego elementu
    int index = findLastElementIndex_int(pStack);

    // Sprawdzamy, czy stos nie jest pusty
    if(index == -1) throwError_int("top_int");

    // Zwracamy wartosc ostatniego elemetu
    return pStack[index]->key;
}

void del_int(IntStackItem **pStack){
    // Znajdujemy index ostatniego elementu
    int index = findLastElementIndex_int(pStack);

    // Sprawdzamy, czy stos nie jest pusty
    if(index == -1) throwError_int("del_int");

    // Kasujemy w przedostatnim elemencie reference do ostatniego elementu
    if(index != 0) pStack[index-1]->pNext= NULL;

    // Kasujemy ostatni element
    free(pStack[index]); // Funkcja free zwalnia zaalokowana pamiec
    pStack[index] = NULL;
}

void printIntStack(IntStackItem **pStack){
    printf("\nPrinting IntStack:");
    IntStackItem *element = pStack[0];

    while(element != NULL){
        printf("\n- %d", element->key);
        element = element->pNext;
    }
}
