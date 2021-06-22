#include "../headers/cellule.h"

cellule_t *creerCelluleDepuisNoeud(noeud_t n, int weight, int height, int colonnes) {
    int valeur;
    cellule_t * cell;
    cell = malloc(sizeof(cellule_t));
    valeur = n.valeur;
    if(cell){
        cell->w = weight;
        cell->h = height;
        cell->i = valeur/colonnes;
        cell->j = valeur%colonnes;
    }
    return cell;
}

void drawCell(SDL_Renderer * renderer,cellule_t * cell){
    SDL_Rect rect;
    rect.x = cell->j*cell->h;
    rect.y = cell->i*cell->w;
    rect.w = cell->w;
    rect.h = cell->h;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer,&rect);
	 SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void drawWall(SDL_Renderer * renderer, int x1, int y1, int x2, int y2){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
