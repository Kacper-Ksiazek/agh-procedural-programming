#include "utils.h"
#include "stdio.h"
#include "stdlib.h"

int getNumberFromUser(char *msg,bool negativeValues){
    int result = 0;
    printf("%s",msg);
    // Pobieramy od usera tekst
    char userInput[30];
    scanf_s("%s",&userInput);
    // Sprawdzamy czy kazdy znak to cyfra
    int i=0;
    char c;
    bool isNegative = false;

    while((c = userInput[i++])){
        if((c >= '0' && c<='9')){
           result = result * 10 + (int)(c-48);
        }else {
            // Sprawdzamy, czy pierwszy znak (uzylismy inkrementacji, wiec przyrownujemy do 1 nie do 0) nie jest minusem, jesli jest to wynik bedzie mial inny znak
            if(i == 1 && c == '-'){
                if(negativeValues) isNegative = true;
                else {
                    printf("Niedozwolona liczba ujemna!");
                    exit(1);
                }
            }
            else {
                printf("Podczas podawania liczby wprowadzono niedozwolony znak: %c", c);
                exit(1);
            }
        }
    }

    return isNegative ? -result : result;
}

static void ensureMemoryAllocation(void *ptr){
    if(ptr == NULL){
        fprintf(stderr,"Memory could not have been allocated!");
        exit(1);
    }
}

Range *getRangeFromUser(void){
    Range *result = (Range*) malloc(sizeof(Range));
    ensureMemoryAllocation(result);
    printf("  Wartosc pojedynczego elementu\n");
    result->min = getNumberFromUser("   -Minimalna: ", true);
    while((result->max = getNumberFromUser("   -Maksymalna: ",true) ) <= result->min){
        printf("   Wartosc maksymalna musi byc wieksza od wartosci minimalnej!!!\n");
    }

    return result;
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


void printTime(float deltaTime){
    int minutes=0, seconds = 0;
    // Minuty
    while(deltaTime>=60){
        minutes++;
        deltaTime-=60;
    }
    // Sekundy
    while(deltaTime>=1){
        seconds++;
        deltaTime-=1;
    }
    float miliseconds = deltaTime * 1000;
    // To co zostalo to milisekundy
    if(minutes) printf("%dmin ");
    if(seconds) printf("%dsec ");

    printf("%.0fms\n",miliseconds);

}


int randomIntFromRange(Range *range){
    // Na to jest wzor po prostu, bez filozofii
    return (rand() % (range->max - range->min + 1)) + range->min;
}

int *createArrayWithRandomValues(int size, Range *range){
    int *p = (int *) calloc(size,sizeof(int));
    // Sprawdzamy, czy udalo sie utworzyc tablice
    ensureMemoryAllocation(p);
    // Wypelniamy ja losowymi wartosciami
    int i= 0;
    while (i!=size) p[i++] = randomIntFromRange(range);
    //
    return p;
}

int *cloneIntArray(const int *array, int size){
    int *result = (int*) calloc(size,sizeof(int));
    ensureMemoryAllocation(result);
    
    for(int i =0;i<size;i++) result[i] = array[i];
    
    return result;
}