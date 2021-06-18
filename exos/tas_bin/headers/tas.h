#ifndef TAS_H
#define TAS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DEFAULT_LENGTH 10

typedef struct tas_s {
    int* array;
    int length;
    int indexToInsert;
} tas_t;

tas_t* creerTas(int);
void ajoutTas(tas_t * tas, int valeur);
void reallocTas(tas_t *, float);
int racineTas(tas_t * tas);
int suppressionRacine(tas_t* tas, int);
void libererTas(tas_t * tas);
void tri_tas(int * tab, int taille);
void afficherTas(tas_t *);
#endif