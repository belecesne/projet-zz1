#ifndef TAS_H
#define TAS_H

#include <stdlib.h>
#define DEFAULT_LENGTH 10

typedef struct tas_s {
    int* array;
    int length;
    int indexToInsert;
} tas_t;

tas_t* creerTas();
void ajoutTas(tas_t * tas, int valeur);
int racineTas(tas_t * tas);
void supressionRacine(tas_t* tas);
void libererTas(tas_t * tas);
void tri_tas(int * tab, int taille);
#endif