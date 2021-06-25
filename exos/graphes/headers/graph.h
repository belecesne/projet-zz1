#ifndef GRAPH
#define GRAPH

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "../headers/union_find.h"

int ** generateRandomGraph(int);
void generateGraphvizGraph(int **, int, char *);
union_find_t * getGraphUnionFind(int ** adjMat, int nbVertices);
void generateConnectedComponents(int **, int nbVertices, union_find_t * part, char * fileName);

#endif