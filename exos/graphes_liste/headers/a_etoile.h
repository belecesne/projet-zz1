#ifndef A_ETOILE
#define A_ETOILE

#include "tas_dijkstra.h"
#include "graph.h"
#include "file.h"
#include <math.h>
#include <limits.h>

float distEuclidienne(int, int, int, int);
float distTchebytchev(int, int, int, int);
float distManhattan(int, int, int, int);
file_t * a_etoile(graph_t * graphe, int rac, float (*dist)(int, int, int, int), int noeudDest, int dimLab);

#endif
