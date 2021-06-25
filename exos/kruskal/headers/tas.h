#ifndef TAS_H
#define TAS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arete.h"
#define DEFAULT_LENGTH 10

typedef arete_t * type_tas_t;

typedef struct tas_s {
	type_tas_t * array;
	int length;
	int indexToInsert;
} tas_t;

tas_t* creerTas(int);
void ajoutTas(tas_t *, type_tas_t);
void reallocTas(tas_t *, float);
type_tas_t racineTas(tas_t *);
type_tas_t suppressionRacine(tas_t*, int);
void libererTas(tas_t *);
int tasVide(tas_t *);
#endif