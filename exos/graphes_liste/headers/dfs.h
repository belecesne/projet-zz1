#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include "file.h"
#include "noeud.h"
#include "labyrinthe.h"
#include <limits.h>

file_t * dfs(labyrinthe_t *, noeud_t);
file_t * dfs_recu(labyrinthe_t *, noeud_t );

#endif
