#ifndef WIFI_H
#define WIFI_H

#include "labyrinthe.h"
#include "file.h"
#include <limits.h>

int trouverCentre(labyrinthe_t *, int);
file_t * limitedDFS(labyrinthe_t *, int, int);

#endif
