#ifndef PROJET_ZZ1_CELLULE_H
#define PROJET_ZZ1_CELLULE_H

#include "noeud.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <SDL2/SDL_image.h>

typedef struct cellule_s {
    noeud_t noeud;
    int i;
    int j;
    int w;
    int h;
    char wall;
} cellule_t;

cellule_t *creerCelluleDepuisNoeud(noeud_t, int, int, int);

void drawCell(SDL_Renderer *, cellule_t *);

void drawWall(SDL_Renderer *, SDL_Point, SDL_Point);

void drawCellText(SDL_Renderer *, cellule_t *,SDL_Texture *, SDL_Texture *);

void drawText(SDL_Renderer * , SDL_Point , int , int, SDL_Texture *);

void drawBack(SDL_Renderer *, int, int, int, int,SDL_Texture *,SDL_Texture *);

void drawEntree(SDL_Renderer *, cellule_t * , SDL_Texture *);

#endif //PROJET_ZZ1_CELLULE_H
