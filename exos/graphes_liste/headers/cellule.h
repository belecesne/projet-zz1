#ifndef PROJET_ZZ1_CELLULE_H
#define PROJET_ZZ1_CELLULE_H
#include "noeud.h"
#include <SDL2/SDL.h>
typedef struct cellule_s {
    int i;
    int j;
    int w;
    int h;
}cellule_t;

cellule_t *creerCelluleDepuisNoeud(noeud_t, int, int, int);
void drawCell(SDL_Renderer *,cellule_t*);
#endif //PROJET_ZZ1_CELLULE_H
