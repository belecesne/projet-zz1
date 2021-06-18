#include "../headers/graph.h"
#include <time.h>

int main() {
    srand(time(NULL));
    graph_t * graphe = nouveau_graphe(10);
    for(int i = 0; i < graphe->nbNoeuds; i++) {
        int nbArretes = rand()%10;
        int * alreadyPresent = calloc(10, sizeof(int));
        for(int j = 0; j < nbArretes; j++) {
            int selectedVertice = rand()%10;
            if(!alreadyPresent[selectedVertice]) {
                insertionArrete(graphe, i, selectedVertice);
                alreadyPresent[selectedVertice] = 1;
            }
        }
        free(alreadyPresent);
    }
    generateGraphvizGraph(graphe, "graph");
    liberer_graphe(graphe);
}