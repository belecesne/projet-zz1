#include "../headers/graph.h"
#include "../headers/maillon_arete.h"
#include "../headers/labyrinthe.h"
#include <time.h>
#define LIGNE 4
#define COLONNE 4

int main() {
	srand(time(NULL));
	labyrinthe_t * labyrinthe = creerLabyrintheQqc(LIGNE, COLONNE,0.5);
	generateGraphvizGraph(labyrinthe->graphe, "graphe_FYP");
	liberer_graphe(labyrinthe->graphe);
	free(labyrinthe);
}