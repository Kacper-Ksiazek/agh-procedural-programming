#include "stack.h" // to jest do typow stosu
#include "stdlib.h" // to jest do calloca i malloca
#include "stdio.h" // printf, exit

// Moje pomocnicze funkcje
int findLastElementIndex(StackItem **pStack);
void throwError(char *functionName);

StackItem** createStack(){
    // W typescript'cie to mozna robic za pomoca operatora "as"
    // Uzywajac okraglych nawiasow przed wyrazaniem ZMIENIAMY JEGO TYP
    // zarowno malloc jak i calloc defaultowo zwracaja "void*" a my chcemy "StackItem*"
    //
    StackItem** result = (StackItem**) calloc( MAX_STACK_LENGTH, sizeof(StackItem));
    // O to sie Onder pamietam z wykladu xDDD sral
    if(result == NULL){
        printf("Blad podczas tworzenia tablicy struktur!!!!");
    }

    return result;
}

int isEmpty(StackItem** pStack){
    // Roznica pomiedzy callockiem a mallockiem jest taka, ze:
    // - uzywajac callocka: default'owa wartosc dla wszystkich elementow tablicy to 0
    // - uzywajac mallocka: brak default'owej wartosci, dlatego podczas
    //                      odwolywania sie do nieistniejacego indexu dzieja sie cuda
    if(pStack[0] == 0) return 1;
    return 0;
}

void push(StackItem** pStack, char x){
    // Musimy uzyc malloca, zeby ominac gargabe collector kompilatora C
    // garbage collector to taki mechanizm, ktory sprzata (kasuje) zmienne po zakonczeniu wykonywania funkcji
    // a my nie chcemy, zeby nasza struktura przepadla, dlatego deklarujemy ja w taki sposob

    StackItem *freshElement = (StackItem*) malloc(sizeof(StackItem));
    freshElement->key = x;
    freshElement->pNext = NULL;

    if(isEmpty(pStack) == 1){
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

char pop(StackItem** pStack){
    // Znajdujemy index ostatniego elementu
    int index = findLastElementIndex(pStack);

    // Sprawdzamy, czy stos nie jest pusty
    if(index == -1) throwError("pop");

    // Zapisujemy znak pod tym indexem
    char result = pStack[index]->key;

    // Uzywamy funkcji del do skasowania ostataniego elementu, jak i referencji do niego w przedostatnim elemencie
    del(pStack);

    // Zwracamy uprzednio zapisany element
    return result;
}

char top(StackItem **pStack){
    // Znajdujemy index ostatniego elementu
    int index = findLastElementIndex(pStack);

    // Sprawdzamy, czy stos nie jest pusty
    if(index == -1) throwError("top");

    // Zwracamy wartosc ostatniego elemetu
    return pStack[index]->key;
}

void del(StackItem **pStack){
    // Znajdujemy index ostatniego elementu
    int index = findLastElementIndex(pStack);

    // Sprawdzamy, czy stos nie jest pusty
    if(index == -1) throwError("del");

    // Kasujemy w przedostatnim elemencie reference do ostatniego elementu
    if(index != 0) pStack[index-1]->pNext= NULL;

    // Kasujemy ostatni element
    free(pStack[index]); // Funkcja free zwalnia zaalokowana pamiec
    pStack[index] = NULL;
}

int findLastElementIndex(StackItem **pStack){
   if(isEmpty(pStack)) return -1;
   int index = 0;
   while(pStack[index]->pNext !=NULL) index++;
    
   return index;
}

void throwError(char *functionName){
    fprintf(stderr, "Proba wywolania %s top na pustym zbiorze", functionName);
    exit(1);
}