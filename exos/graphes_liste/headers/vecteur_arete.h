#ifndef PROJET_ZZ1_ARRAY_LIST_H
#define PROJET_ZZ1_ARRAY_LIST_H
#include "arete.h"
#define DEFAULT_ARRAY_SIZE 32

typedef arete * vec_type;

typedef struct vecteur_s {
    vec_type * array;
    int tailleCourante;
    int taille;
}vecteur_t;

vecteur_t * creerVecteur(int);
vecteur_t * reallouerVecteur(vecteur_t * );
void insererQueueVecteur(vecteur_t *, vec_type);
void supprimerVecteur(vecteur_t * , int);


#endif //PROJET_ZZ1_ARRAY_LIST_H
