#ifndef LISTE
#define LISTE

#include <stdlib.h>
#include <stdio.h>
#include "booleen.h"
#include "erreur.h"

typedef struct maillon_s {
	int				  valeur;
    struct maillon_s    * suivant;
} maillon_t;

maillon_t * nouvelle_liste();
maillon_t * nouveau_maillon(int, erreur_t *);
void adjonction(maillon_t **, maillon_t *, erreur_t *);
void suppression(maillon_t **);
void afficher_liste(maillon_t **);
void liberer_liste(maillon_t **);
#endif