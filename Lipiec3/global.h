#ifndef LIPIEC_3_GLOBAL_H
#define LIPIEC_3_GLOBAL_H

typedef struct PQInfo{
    int nKey;
    int *pTab;

} PQInfo;

// Typ strukturalny o nazwie PQInfo z polami nKey( int ) oraz pTab( int* - tablica dwuelementowa)
//
// Zdefiniowac stala preprocesora PQINFO jako typ strukturalny PQInfo    //
// nazwy PQINFO - uzywac WSZEDZIE#define PQINFO PQInfo

#define PQINFO PQInfo

#endif
