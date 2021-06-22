#ifndef PROJET_ZZ1_NOEUD_H
#define PROJET_ZZ1_NOEUD_H

#include <stdlib.h>

typedef struct noeud_s {
    int valeur;
    char wall;
} noeud_t;

void orientiation(noeud_t *, noeud_t *, int);

#endif //PROJET_ZZ1_NOEUD_H
