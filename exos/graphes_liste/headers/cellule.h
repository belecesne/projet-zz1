#ifndef PROJET_ZZ1_CELLULE_H
#define PROJET_ZZ1_CELLULE_H
#include "noeud.h"
#include <SDL2/SDL.h>
typedef struct cellule_s {
    noeud_t noeud;
    int i;
    int j;
    int w;
    int h;
}cellule_t;

cellule_t *creerCelluleDepuisNoeud(noeud_t, int, int, int);
void drawCell(SDL_Renderer *,cellule_t*);
void drawWall(SDL_Renderer * , SDL_Point , SDL_Point);
#endif //PROJET_ZZ1_CELLULE_H
