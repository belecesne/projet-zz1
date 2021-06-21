#ifndef GRAPH_LIST
#define GRAPH_LIST
#include "maillon_graphe.h"
#include "maillon_arete.h"
#include "partition.h"

typedef struct graph_s {
    maillon_arete_t * listeAretes;
    int nbNoeuds;
} graph_t;

graph_t * nouveau_graphe(int);
void insertionArrete(graph_t *,arete_t*);
void liberer_graphe(graph_t *);
void generateGraphvizGraph(graph_t *, char *);
partition_t *getParitionFromGraph(graph_t *);
void generateConnectedComponents(graph_t *, char *);

#endif //GRAPH_LIST
