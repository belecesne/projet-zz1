#ifndef UNION_FIND_ADRIEN_ZZ1_UNION_FIND_H
#define UNION_FIND_ADRIEN_ZZ1_UNION_FIND_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste.h"

#define DEFAULT_UNION_FIND_SIZE 11

typedef struct union_find_t {
    int *partition;
    int *level;
    int size;
    liste_t **classes;
} union_find_t;


union_find_t *createUnionFind(int, int *);

void freeUnionFind(union_find_t *);

void initUnionFind(union_find_t *);

void printUnionFind(union_find_t *);

int rootNodeUnionFind(union_find_t *, int);

void fusionUnionFind(union_find_t *, int, int);

void printClassUnionFind(union_find_t *, int);

void printAllClassesUnionFind(union_find_t *);

void makeGraphvizGraph(union_find_t *, char *);

#endif //UNION_FIND_ADRIEN_ZZ1_UNION_FIND_H
