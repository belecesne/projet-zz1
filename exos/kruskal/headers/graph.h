#ifndef GRAPH_LIST
#define GRAPH_LIST
#include "maillon_arete.h"
#include "partition.h"
#include "tas.h"

typedef struct graph_s {
    maillon_arete_t * listeAretes;
    int nbNoeuds;
} graph_t;

graph_t * nouveauGraphe(int);
void insertionArrete(graph_t *,arete_t*);
void libererGraphe(graph_t *);
void generateGraphvizGraph(graph_t *, char *);
partition_t *getParitionFromGraph(graph_t *);
void generateConnectedComponents(graph_t *, char *);
graph_t * kruskal(graph_t *);

#endif //GRAPH_LIST
