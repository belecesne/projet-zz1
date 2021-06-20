#ifndef GRAPH_MAILLON
#define GRAPH_MAILLON

#include <stdlib.h>
#include <stdio.h>

typedef struct maillon_graphe_s {
	int				  noeud;
    struct maillon_graphe_s    * suivant;
} maillon_graphe_t;


maillon_graphe_t * nouveau_maillon_graphe(int);
void adjonction_graphe(maillon_graphe_t **, maillon_graphe_t *);
void suppression_graphe(maillon_graphe_t **);
#endif  // LISTE_CHAINEE_H
