#include "stdio.h"
#include "stdlib.h"

#include "tools.h"
#include "PQueue.h"
#include "ERROR_MESSAGES.h"

/**
 * Print single user info struct
 *
 * @param p pointer to user info
 */
void printUserInfo(const void *p);


/**
 * Compare two queue elements
 *
 * @param a pointer to user info
 * @param b pointer to user info
 * @return 1 if they match, 0 otherwise
 */
int compareTwoQueueElements(const void *a, const void *b);


/**
 * Free memory allocated for single user info
 *
 * @param p pointer to user info
 */
void freeMemory(const void *p);


/**
 * Allocate memory required for structure and returns pointer to it
 *
 * @param key value of nKey property
 * @param a value of nTab index 0
 * @param b value of nTab index 1
 * @return pointer to PQINFO structure
 */
PQINFO *createUserInfo(int key, int a, int b);


int main() {
    PQINFO *element1 = createUserInfo(1, 4, 5);
    PQINFO *element2 = createUserInfo(2, 7, 8);
    PQINFO *element3 = createUserInfo(3, 9, 10);
    PQINFO *element4 = createUserInfo(4, 11, 12);
    PQINFO *element5 = createUserInfo(5, 13, 14);
    PQINFO *element6 = createUserInfo(6, 15, 16);
    PQINFO *element7 = createUserInfo(7, 17, 18);
    PQINFO *element8 = createUserInfo(8, 19, 20);

    // 1. wykreowac kolejke 20-sto elementowa

    PQueue *queue = PQCreate(20);


    // 2. dodac 6 elementow z roznymi priorytetami i w różnej kolejnosci priorytetów - wydrukowac

    printf("-----\nKROK 2: Dodanie 6 elementow do kolejki: \n");
    PQEnqueue(queue, 9, element1);   // 1
    PQEnqueue(queue, 8, element2);   // 2
    PQEnqueue(queue, 7, element3);   // 3
    PQEnqueue(queue, 10, element4);  // 4
    PQEnqueue(queue, 1, element5);   // 5
    PQEnqueue(queue, -1, element6);  // 6

    PQPrint(queue, printUserInfo, 0);


    // 3. usunac z kolejki (z najwiekszym priorytetem)  - wydrukowac

    printf("\n\n\n-----\nKROK 3: Usuniecie elementu z najwyzszym priorytetem: \n");
    printf("\nUsuniety element z najwyzszym priorytetem: \n");
    printUserInfo(PQDequeue(queue));
    printf("\n");
    PQPrint(queue, printUserInfo, 0);


    // 4. dodac dwa elementy - wydrukowac

    printf("\n\n\n-----\nKROK 4: Dodanie 2 dodatkowych elementow: \n");
    PQEnqueue(queue, -200, element7);  // 1
    PQEnqueue(queue, 20, element8);    // 2
    PQPrint(queue, printUserInfo, 0);


    // 5. wyszukac jeden element

    printf("\n\n\n-----\nKROK 5: Wyszukanie pojedynczego elementu: \n");
    printf("\nPozycja elementu o kluczu = 7 wynosi: %d", PQFind(queue, element7, compareTwoQueueElements));


    // 6. zwiekszyc mu priorytet (unikalny) - wydrukowac

    printf("\n\n\n-----\nKROK 6: Zwiekszenie priorytetu pojedynczego elementu (elementu o kluczu 7): \n");
    PQSetPrior(queue, 300, element7, compareTwoQueueElements);
    PQPrint(queue, printUserInfo, 0);


    // 7. zmniejszyc priorytet innemu elementowi (unikalny) - wydrukowac

    printf("\n\n\n-----\nKROK 7: Zmniejszenie priorytetu pojedynczego elementu (elementu o kluczu 6): \n");
    PQSetPrior(queue, -10, element6, compareTwoQueueElements);
    PQPrint(queue, printUserInfo, 0);


    // 8. usuac cala kolejke

    printf("\n\n\n-----\nKROK 8: Usunac cala kolejke: \n");
    PQRelease(&queue, freeMemory);
    printf("\n%s", queue == NULL ? "Kolejka zostala wyczyszczona" : "BLAD! KOLEJKA NIE ZOSTALA WYCZYSZCZONA");


    // 9. przetestowac jak bedzie sie zachowywac modul jesli powtorza sie priorytety niektorych elementow
    //    (zmienic priorytet np na maksymalny - powtorzy sie i sciagnac dwa razy, po kazdym drukowanie)
    printf("\n\n\n-----\nKROK 9 Sytuacja w ktorej powtorzy sie najwiekszy priorytet: \n");

    queue = PQCreate(10);
    element1 = createUserInfo(1, 4, 5);
    element2 = createUserInfo(2, 7, 8);
    element3 = createUserInfo(3, 9, 10);
    element4 = createUserInfo(4, 11, 12);
    element5 = createUserInfo(5, 13, 14);

    PQEnqueue(queue, 10, element1);
    PQEnqueue(queue, 10, element2);
    PQEnqueue(queue, 10, element3);
    PQEnqueue(queue, 2, element4);
    PQEnqueue(queue, 9, element5);

    PQPrint(queue, printUserInfo, 0);

    printf("\n\nSciaganie elementow: \n");

    printf("1. Pierwszy sciagniety zostal element o kluczu: %d\n", PQDequeue(queue)->nKey);
    PQPrint(queue, printUserInfo, 0);

    printf("\n\n2. Drugi sciagniety zostal element o kluczu: %d\n", PQDequeue(queue)->nKey);
    PQPrint(queue, printUserInfo, 0);

    printf("\n\n3. Trzeci sciagniety zostal element o kluczu: %d\n", PQDequeue(queue)->nKey);
    PQPrint(queue, printUserInfo, 0);

    printf("\n\nWNIOSEK: Elementy z rownymi priorytetami zostaja sciagane w kolejnosci, w ktorej zostaly dodane");

    return 0;
}


void printUserInfo(const void *p) {
    // We have to assume that pointer is type of PQINFO
    const PQINFO *info = (PQINFO *) p;

    printf("   Klucz: %d\n", info->nKey);
    printf("   Tablica: [%d,%d]", info->pTab[0], info->pTab[1]);
}

PQINFO *createUserInfo(int key, int a, int b) {
    PQInfo *result = (PQINFO *) malloc(sizeof(PQINFO));
    checkPointer(result, ERROR_MEMORY_ALLOCATION_PQINFO);

    int *pTab = calloc(2, sizeof(int));
    checkPointer(result, ERROR_MEMORY_ALLOCATION_PTAB);

    pTab[0] = a;
    pTab[1] = b;

    result->nKey = key;
    result->pTab = pTab;

    return result;
};

void freeMemory(const void *p) {
    // We have to assume that pointer is type of PQINFO
    const PQINFO *info = (PQINFO *) p;

    free(info->pTab);
    free((void *) info);
}

int compareTwoQueueElements(const void *a, const void *b) {
    // We have to assume that both pointers are type of PQINFO
    const PQINFO *info1 = (PQINFO *) a;
    const PQINFO *info2 = (PQINFO *) b;

    if (info1->nKey != info2->nKey || info1->pTab[0] != info2->pTab[0] || info1->pTab[1] != info2->pTab[1]) return 0;
    return 1;
}
