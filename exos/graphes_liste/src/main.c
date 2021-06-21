#include "../headers/graph.h"
#include "../headers/maillon_arete.h"
#include "../headers/labyrinthe.h"
#include <time.h>
#define LIGNE 50
#define COLONNE 50

int main() {
	srand(time(NULL));
	labyrinthe_t * labyrinthe = creerLabyrintheArbo(LIGNE, COLONNE);
	generateGraphvizGraph(labyrinthe->graphe, "graphe_FY");
	liberer_graphe(labyrinthe->graphe);
	free(labyrinthe);
}