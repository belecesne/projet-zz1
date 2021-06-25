#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "tas_dijkstra.h"
#include "labyrinthe.h"
#include "graph.h"
#include "file.h"
#include <limits.h>

file_t * dijkstra(labyrinthe_t *, noeud_t , noeud_t, noeud_t *, int *);

#endif
