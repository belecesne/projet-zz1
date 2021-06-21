#ifndef PROJET_ZZ1_LABYRINTHE_H
#define PROJET_ZZ1_LABYRINTHE_H

#include "graph.h"

typedef struct labyrinthe_s{
	graph_t* graphe;
	int lignes;
	int colonnes;
} labyrinthe_t;

labyrinthe_t * creerLabyrintheArbo(int, int);
void fisherYates(graph_t*, int, int);
void kruskalFisherYates(graph_t*, labyrinthe_t*);

#endif //PROJET_ZZ1_LABYRINTHE_H
