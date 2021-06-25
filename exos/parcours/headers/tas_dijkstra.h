#ifndef TAS_DIJKSTRA_H
#define TAS_DIJKSTRA_H

#include <stdlib.h>
#include "noeud.h"
#include <stdio.h>
#include <string.h>
#define DEFAULT_LENGTH_DIJKSTRA 10

typedef struct elem_tas_dijkstra_s {
    noeud_t som;
    int dist;
} elem_tas_dijkstra_t;

typedef struct tas_dijktra_s {
    elem_tas_dijkstra_t * array;
    int length;
    int indexToInsert;
} tas_dijkstra_t;

tas_dijkstra_t* creerTasDijktra();
void ajoutTasDijkstra(tas_dijkstra_t * , noeud_t , int);
void reallocTasDijkstra(tas_dijkstra_t *, float);
elem_tas_dijkstra_t racineTasDijkstra(tas_dijkstra_t * );
elem_tas_dijkstra_t suppressionRacineDijkstra(tas_dijkstra_t* );
void libererTasDijkstra(tas_dijkstra_t * );
int tasVideDijkstra(tas_dijkstra_t *);
void modifValeurTasDijkstra(tas_dijkstra_t *, noeud_t , int);
#endif
