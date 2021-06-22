#ifndef PROJET_ZZ1_LABYRINTHE_H
#define PROJET_ZZ1_LABYRINTHE_H

#include "graph.h"

typedef struct labyrinthe_s{
	graph_t* graphe;
	int lignes;
	int colonnes;
} labyrinthe_t;

labyrinthe_t * creerLabyrintheQqc(int, int, double);
maillon_arete_t * fisherYates(arete_t **, int, int);
void kruskalFisherYatesProba(arete_t **, labyrinthe_t*, double);

#endif //PROJET_ZZ1_LABYRINTHE_H
