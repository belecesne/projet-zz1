#ifndef LISTE
#define LISTE

#include <stdlib.h>
#include <stdio.h>
#include "booleen.h"
#include "erreur.h"

typedef struct maillon_s {
	float				  valeur;
	int 			 	  i;
	int 				  j;
    struct maillon_s    * suivant;
} maillon_t;

maillon_t * nouvelle_liste();
maillon_t * nouveau_maillon(float, int, int, erreur_t *);
void adjonction(maillon_t **, maillon_t *, erreur_t *);
void suppression(maillon_t **);
void afficher_liste(maillon_t **);
void liberer_liste(maillon_t **);
maillon_t** recherche_prec_selon_fonction(maillon_t** pointeur_debut_liste, float valeur, booleen_t (*fonction_recherche) (float, float));
void sauvegarder_liste_fichier(maillon_t **, const char *, erreur_t *);
#endif