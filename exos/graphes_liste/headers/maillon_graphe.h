#ifndef GRAPH_MAILLON
#define GRAPH_MAILLON

#include <stdlib.h>
#include <stdio.h>

typedef struct maillon__graphe_s {
	int				  noeud;
    struct maillon_s    * suivant;
} maillon_graphe_t;


maillon_graphe_t * nouveau_maillon(int);
void adjonction(maillon_graphe_t **, maillon_graphe_t *);
void suppression(maillo_graphe_t **);
#endif  // LISTE_CHAINEE_H
