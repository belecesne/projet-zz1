#ifndef PROJET_ZZ1_ARETE_H
#define PROJET_ZZ1_ARETE_H

#include "noeud.h"
#include <stdlib.h>

typedef struct arete_s {
    noeud_t n1;
    noeud_t n2;
    int poids;
}arete_t;

arete_t * creerArete(noeud_t, noeud_t, int);

#endif //PROJET_ZZ1_ARETE_H
