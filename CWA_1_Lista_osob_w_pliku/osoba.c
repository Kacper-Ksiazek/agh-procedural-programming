#include "osoba.h"
#include "stdlib.h"
#include "stdio.h"
#include "utils.h"
#include "string.h"

#define DLUGOSC_LINI 64


Osoba* wczytaj_osoby_z_pliku(char* nazwa_pliku){
    Osoba *result = (Osoba*)calloc(100, sizeof(Osoba));
    int result_length = 0;

    FILE *ptr;
    ptr = fopen(nazwa_pliku,"r");

    if(ptr == NULL) {
        printf("Nie mozna odnalezc pliku \n");
        return NULL;
    }

    char line[DLUGOSC_LINI];

    Osoba new_person = {};

    while (!feof(ptr)){
        fgets(line,DLUGOSC_LINI,ptr);

        if(line[0] == '{' ) continue;
        if(line[0] == '}'){
//            printf("Nowa osoba:\nId: %d\nImie: %s\nNazwisko: %s\nWiek: %d\n",new_person.id,new_person.imie,new_person.nazwisko,new_person.wiek);
            result[result_length++] = new_person;
            continue;
        }

        KeyValuePair data = extract_data_from_a_single_line(line);

        if(strcmp(data.key,"id") == 0) new_person.id = atoi(data.value);

        else if(strcmp(data.key,"imie")==0) new_person.imie = data.value;

        else if(strcmp(data.key, "nazwisko") == 0) new_person.nazwisko = data.value;

        else if(strcmp(data.key, "wiek") == 0) new_person.wiek =atoi(data.value);
    }

    return result;
}