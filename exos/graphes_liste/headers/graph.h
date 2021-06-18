#ifndef GRAPH_LIST
#define GRAPH_LIST
#include "maillon.h"

typedef struct graph_s {
    struct maillon_s * liste;
    int nbNoeuds;
}graph_t;

graph_t * nouveau_graphe();
void insertionArrete(graph_t *, maillon_t *);
void liberer_graphe(graph_t *);
void generateGraphvizGraph(graph_t *, char *);

#endif //GRAPH_LIST
