#ifndef TAS_H
#define TAS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DEFAULT_LENGTH 10

typedef struct elem_tas_s {
    int som1;
    int som2;
    int poids;
} elem_tas_t;

typedef struct tas_s {
    elem_tas_t * array;
    int length;
    int indexToInsert;
} tas_t;

tas_t* creerTas();
void ajoutTas(tas_t * tas, elem_tas_t valeur);
void reallocTas(tas_t *, float);
elem_tas_t racineTas(tas_t * tas);
elem_tas_t suppressionRacine(tas_t* tas);
void libererTas(tas_t * tas);
int tasVide(tas_t *);
#endif
