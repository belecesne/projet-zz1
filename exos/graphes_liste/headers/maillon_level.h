#ifndef PROJET_ZZ1_MAILLON_LEVEL_H
#define PROJET_ZZ1_MAILLON_LEVEL_H

#include "liste.h"

typedef struct maillon_level_s {
	int                 level;
	liste_t *          class;
	struct maillon_level_s    * prec;
	struct maillon_level_s    * suivant;
} maillon_level_t;


maillon_level_t * nouveau_maillon_level(liste_t *);
void adjonction_level(maillon_level_t*, maillon_level_t **, maillon_level_t*);
void suppression_level(maillon_level_t *, maillon_level_t *);
#endif //PROJET_ZZ1_MAILLON_LEVEL_H
