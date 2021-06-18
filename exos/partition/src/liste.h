#ifndef LISTE_CHAINEE_H
#define LISTE_CHAINEE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct maillon_s {
	int				  valeur;
    struct maillon_s    * suivant;
} maillon_t;

maillon_t * nouvelle_liste();
maillon_t * nouveau_maillon(int);
void adjonction(maillon_t **, maillon_t *);
void suppression(maillon_t **);
void afficher_liste(maillon_t **);
void liberer_liste(maillon_t **);
#endif  // LISTE_CHAINEE_H