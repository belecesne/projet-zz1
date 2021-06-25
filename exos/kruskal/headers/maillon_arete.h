#ifndef PROJET_ZZ1_MAILLON_ARETE_H
#define PROJET_ZZ1_MAILLON_ARETE_H

#include "arete.h"

typedef struct maillon_arete_s {
    arete_t * arete;
    struct maillon_arete_s * suivant;
} maillon_arete_t;

#endif //PROJET_ZZ1_MAILLON_ARETE_H


maillon_arete_t *creerMaillonArete(arete_t *);

void insertionTeteArete(maillon_arete_t **, maillon_arete_t *);

void libererListeArretes(maillon_arete_t *);