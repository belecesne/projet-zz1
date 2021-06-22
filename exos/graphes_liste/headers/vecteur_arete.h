#ifndef PROJET_ZZ1_ARRAY_LIST_H
#define PROJET_ZZ1_ARRAY_LIST_H

#include "arete.h"
#include <string.h>

#define DEFAULT_VECTOR_SIZE 32

typedef arete_t *vec_arete_type;

typedef struct vecteur_s {
    vec_arete_type *array;
    int tailleCourante;
    int taille;
} vecteur_arete_t;

vecteur_arete_t *creerVecteurArete(int);

void reallouerVecteurArete(vecteur_arete_t *);

void insererQueueVecteurArete(vecteur_arete_t *, vec_arete_type);

void supprimerVecteurArete(vecteur_arete_t **, int);

void libererVecteurArete(vecteur_arete_t *);

#endif //PROJET_ZZ1_ARRAY_LIST_H
