#include "stdio.h"
#include "osoba.h"

int main(){
    Osoba* lista_osob = wczytaj_osoby_z_pliku("../lista.txt");

    printf("%s %s", lista_osob[1].imie, lista_osob[1].nazwisko);

    return 0;
}