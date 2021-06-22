#ifndef PROJET_ZZ1_ARRAY_LIST_H
#define PROJET_ZZ1_ARRAY_LIST_H
#include "arete.h"
#define DEFAULT_VECTOR_SIZE 32

typedef arete * vec_type;

typedef struct vecteur_s {
    vec_type * array;
    int tailleCourante;
    int taille;
}vecteur_t;

vecteur_t * creerVecteurArete(int);
void reallouerVecteurArete(vecteur_t * );
void insererQueueVecteurArete(vecteur_t *, vec_type);
void supprimerVecteurArete(vecteur_t * , int);
void libererVecteurArete(vecteur_t *);

#endif //PROJET_ZZ1_ARRAY_LIST_H
