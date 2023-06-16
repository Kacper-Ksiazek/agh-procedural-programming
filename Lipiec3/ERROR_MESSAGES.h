#pragma once

// Memory allocation

#define ERROR_MEMORY_ALLOCATION_QUEUE "Nie udalo sie zaalokowac pamieci dla kolejki (PQueue)"
#define ERROR_MEMORY_ALLOCATION_PQITEM "Nie udalo sie zaalkowac pamieci dla elementu kolejki (PQItem)"
#define ERROR_MEMORY_ALLOCATION_PQINFO "Nie udalo sie zaalokowac pamieci dla informacji uzytkownika (PQINFO)"

// NULL pointers

#define ERROR_NULL_POINTER_QUEUE "Wskaznik na kolejke jest rowny NULL"
#define ERROR_NULL_POINTER_PQITEM_ARRAY "Wskaznik na tablice informacji uzytkownika (PQINFO) jest rowny NULL"
#define ERROR_NULL_POINTER_PQINFO "Wskaznik na informacje uzytkownika (PQINFO) jest rowny NULL"
#define ERROR_NULL_POINTER_FREEMEMORY_FN "Wskaznik na funkcje odpowiedzalna za czyszczenie pamieci jest rowny NULL"
#define ERROR_NULL_POINTER_COMPARE_FN "Wskaznik na funkcje porownujaca dwie informacje uzytkownika jest rowny NULL"
#define ERROR_NULL_POINTER_PRINT_FN "Wskaznik na funkcje wyswietlajaca pojedyncza informacje uzytkownika jest rowny NULL"

#define ERROR_QUEUE_CAPACITY_EXCEEDED "Usiagnieto maksymalny rozmiar kolejki, nie mozna do niej dodac wiekszej ilosci elementow"