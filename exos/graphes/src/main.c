#include "../headers/graph.h"

int main() {
    srand(time(NULL));
    int ** graphe = generateRandomGraph(15);
    generateGraphvizGraph(graphe, 15, "graph");
    union_find_t * part = getGraphUnionFind(graphe, 15);
    makeGraphvizGraph(part, "part");
    generateConnectedComponents(graphe, 15, part, "cc");
    freeUnionFind(part);
    for(int i = 0; i < 15; i++) {
        free(graphe[i]);
    }
    free(graphe);
}