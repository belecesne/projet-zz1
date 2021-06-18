#ifndef GRAPH_LIST
#define GRAPH_LIST
#include "../headers/maillon_graphe.h"
#include "../headers/union_find.h"

typedef struct graph_s {
    struct maillon_s ** tabListes;
    int nbNoeuds;
}graph_t;

graph_t * nouveau_graphe(int);
void insertionArrete(graph_t *, int, int);
void liberer_graphe(graph_t *);
void generateGraphvizGraph(graph_t *, char *);

#endif //GRAPH_LIST
