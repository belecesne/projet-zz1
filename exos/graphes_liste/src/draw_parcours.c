#include "../headers/draw_parcours.h"

int drawParcours(SDL_Renderer * renderer, cellule_t * cellCourante, cellule_t ** tabCellules, int colonnes){
    colorierVoisins(renderer, cellCourante, tabCellules, colonnes);
    cellCourante->etat = 2;
    return 0;

}

void reinitEtat(cellule_t ** tabCellules, int taille){
    for(int i = 0; i < taille; tabCellules[i++]->etat = 0);
}