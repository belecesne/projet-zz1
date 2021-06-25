#ifndef WIFI_H
#define WIFI_H

#include "labyrinthe.h"
#include "file.h"
#include <limits.h>

int trouverCentre(labyrinthe_t *, int);
int limitedDFS(labyrinthe_t *, int, int, int *);
file_t * posBornesWifi(labyrinthe_t *, int);
#endif
