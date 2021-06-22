#ifndef PROJET_ZZ1_ARRAY_LIST_H
#define PROJET_ZZ1_ARRAY_LIST_H

#define DEFAULT_ARRAY_SIZE 32

typedef arete * vec_type;

typedef struct vecteur_s {
    vec_type * array;
    int tailleCourante;
    int taille;
}vecteur_t;

vecteur_t * creerVecteur(int);

#endif //PROJET_ZZ1_ARRAY_LIST_H
