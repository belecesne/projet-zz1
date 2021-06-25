#ifndef FILE_H
#define FILE_H

#define TAILLE_BASE 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef int elem_file_t;

typedef struct file_s {
    elem_file_t * tab;
    int tete;
    int queue;
    int taille;
    int nb_elements;
} file_t;

void affiche_elem_file_t(elem_file_t, char *, char *);
file_t * creer_file();
void enfiler(file_t*, elem_file_t);
void liberer_file(file_t*);
void vider_file(file_t *);
int file_est_vide(file_t*);
int file_est_pleine(file_t *);
elem_file_t tete_file(file_t*);
void defiler(file_t*);
void afficher_file(file_t *);

#endif
