#include "../headers/graph.h"
#include <time.h>

int main() {
    srand(time(NULL));
    graph_t * graphe = nouveau_graphe();
    graphe ->nbNoeuds = 10;
    maillon_t * nouv;
    for(int i = 0; i < graphe->nbNoeuds; i++) {
        int nbArretes = rand()%10;
        int * alreadyPresent = calloc(10, sizeof(int));
        for(int j = 0; j < nbArretes; j++) {
            int selectedVertice = rand()%10;
            if(!alreadyPresent[selectedVertice]) {
                nouv = nouveau_maillon(i, selectedVertice);
                if(nouv != NULL) {
                    printf("%d %d\n", nouv->noeud1, nouv->noeud2);
                }
                insertionArrete(graphe, nouv);
                alreadyPresent[selectedVertice] = 1;
            }
        }
        free(alreadyPresent);
    }
    generateGraphvizGraph(graphe, "graph");
    liberer_graphe(graphe);
}