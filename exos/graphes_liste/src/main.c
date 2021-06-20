#include "../headers/graph.h"
#include <time.h>

int main() {
    srand(time(NULL));
    graph_t * graphe = nouveau_graphe(10);
    for(int i = 0; i < graphe->nbNoeuds; i++) {
        for(int j = 0; j < 2; j++) {
            int selectedVertice = rand()%10;
            insertionArrete(graphe, i, selectedVertice);
        }
    }
    generateGraphvizGraph(graphe, "graph");
    generateConnectedComponents(graphe, "cc");
    liberer_graphe(graphe);
}