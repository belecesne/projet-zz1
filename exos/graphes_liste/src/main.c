#include "../headers/graph.h"
#include "../headers/maillon_arete.h"
#include <time.h>

int main() {
    graph_t *graphe;
    graphe = genererGrapheGrille(4, 4);
	generateGraphvizGraphGrid(graphe, "graphe_grille", 4);
	liberer_graphe(graphe);
}