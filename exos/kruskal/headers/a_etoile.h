#ifndef A_ETOILE
#define A_ETOILE

#include "tas_dijkstra.h"
#include "labyrinthe.h"
#include "graph.h"
#include "file.h"
#include <math.h>
#include <limits.h>

float distEuclidienne(int, int, int, int);
float distTchebytchev(int, int, int, int);
float distManhattan(int, int, int, int);
file_t * a_etoile(labyrinthe_t *, noeud_t , float (*)(int, int, int, int), noeud_t , int, noeud_t *, int *);

#endif
