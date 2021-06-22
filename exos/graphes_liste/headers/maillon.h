#ifndef LISTE_CHAINEE_H
#define LISTE_CHAINEE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct maillon_s {
    int valeur;
    struct maillon_s *suivant;
} maillon_t;


maillon_t *nouveau_maillon(int);

void adjonction(maillon_t **, maillon_t *);

void suppression(maillon_t **);

#endif  // LISTE_CHAINEE_H