#ifndef PROJET_ZZ1_WIFI_PROBA_H
#define PROJET_ZZ1_WIFI_PROBA_H
#include "labyrinthe.h"
#include "file.h"
#include "tas_dijkstra.h"
#include "math.h"
#include <limits.h>
#define MAX(a,b) (((a)>(b))?(a):(b))

int longueurPlusCourtChemin(labyrinthe_t *, noeud_t, noeud_t);
int distancePlusLoin(labyrinthe_t *, noeud_t, noeud_t *);
noeud_t dfs_max(labyrinthe_t *, noeud_t );
void recuitSimule(labyrinthe_t *, noeud_t *, int, double);
#endif //PROJET_ZZ1_WIFI_PROBA_H
