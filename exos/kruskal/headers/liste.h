#ifndef UNIONFIND_ZZ1_LISTE_H
#define UNIONFIND_ZZ1_LISTE_H
#include "maillon.h"

typedef struct liste_s {
    struct maillon_s * tete;
    struct maillon_s * queue;
    int racine;
}liste_t;

liste_t * nouvelle_liste();
void insertionTete(liste_t *, maillon_t *);
void afficher_liste(liste_t *,const char *);
void liberer_liste(liste_t *);
void fusion_liste(liste_t *, liste_t *);


#endif //UNIONFIND_ZZ1_LISTE_H
