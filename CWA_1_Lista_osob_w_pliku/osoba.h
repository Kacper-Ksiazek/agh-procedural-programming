#ifndef CLION_OSOBA_H
#define CLION_OSOBA_H

typedef struct Osoba{
    char* imie;
    char* nazwisko;
    int wiek;
    int id;
} Osoba;

void dodaj_osobe(Osoba* osoba);

Osoba* wczytaj_osoby_z_pliku(char* nazwa_pliku);

#endif //CLION_OSOBA_H
