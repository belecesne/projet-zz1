#ifndef PROJET_ZZ1_MAILLON_CLASSE_H
#define PROJET_ZZ1_MAILLON_CLASSE_H

#include "liste.h"


typedef struct maillon_classe_s {
    liste_t *classe;
    struct maillon_classe_s *suivant;
} maillon_classe_t;

void insertion_tete_classe(maillon_t **, maillon_t *);

maillon_classe_t *creerMaillon(liste_t *);

maillon_classe_t *tableauVersListe(liste_t **, int);

void libererListeClasses(maillon_classe_t *);

#endif //PROJET_ZZ1_MAILLON_CLASSE_H
