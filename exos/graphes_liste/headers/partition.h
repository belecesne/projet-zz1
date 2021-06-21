#ifndef UNION_FIND_ADRIEN_ZZ1_UNION_FIND_H
#define UNION_FIND_ADRIEN_ZZ1_UNION_FIND_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste.h"
#include "maillon_classe.h"

#define DEFAULT_UNION_FIND_SIZE 11

typedef struct partition_s {
    int *parent;
    int *level;
    int size;
    liste_t **classes;
} partition_t;


partition_t *createPartition(int, int *);

void freePartition(partition_t *);

void initPartition(partition_t *);

void printPartition(partition_t *);

int rootNodePartition(partition_t *, int);

void fusionPartition(partition_t *, int, int);

void printClassPartition(partition_t *, int);

void printAllClassesPartition(partition_t *);

void makeGraphvizGraph(partition_t *, char *);

liste_t *getClassNode(partition_t *, int);

maillon_classe_t *getAllClasses(partition_t *);

#endif //UNION_FIND_ADRIEN_ZZ1_UNION_FIND_H
