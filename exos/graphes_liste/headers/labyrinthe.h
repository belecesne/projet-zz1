#ifndef PROJET_ZZ1_LABYRINTHE_H
#define PROJET_ZZ1_LABYRINTHE_H

#include "graph.h"
#include "cellule.h"


typedef struct labyrinthe_s{
	graph_t* graphe;
	cellule_t ** tableauCellules;
	int lignes;
	int colonnes;
} labyrinthe_t;

labyrinthe_t * creerLabyrintheQqc(int, int, int, int, double);
void fisherYates(graph_t *);
void kruskalFisherYatesProba(graph_t *, labyrinthe_t*, double);
void kruskalFisherYates(graph_t *, labyrinthe_t *);
void libererLabyrinthe(labyrinthe_t *);
void creerMur(labyrinthe_t *);
#endif //PROJET_ZZ1_LABYRINTHE_H
