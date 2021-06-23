#include "../headers/draw_parcours.h"

int drawParcours(SDL_Renderer * renderer, file_t * file, cellule_t * cellCourante, cellule_t ** tabCellules, int colonnes){
    colorierVoisins(renderer, cellCourante, tabCellules, colonnes);
    cellCourante->etat = 2;
}

void reinitEtat(cellule_t ** tabCellules, int taille){
    for(int i = 0; i < taille; tabCellules[i++]->etat = 0);
}