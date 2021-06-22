#ifndef GRAPH_LIST
#define GRAPH_LIST
#include "maillon_graphe.h"
#include "maillon_arete.h"
#include "partition.h"
#include "vecteur_arete.h"

typedef struct graph_s {
    vecteur_t * listeAretes;
    int nbNoeuds;
} graph_t;

graph_t * nouveauGraphe(int);
void insertionArrete(graph_t *,arete_t*);
void libererGraphe(graph_t *);
void generateGraphvizGraph(graph_t *, char *);
void generateGraphvizGraphGrid(graph_t*, char*, int);
partition_t *getParitionFromGraph(graph_t *);
void generateConnectedComponents(graph_t *, char *);
graph_t * genererGrapheGrille(int, int);

#endif //GRAPH_LIST
