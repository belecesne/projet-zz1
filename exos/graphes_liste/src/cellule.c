#include "../headers/cellule.h"

cellule_t *creerCelluleDepuisNoeud(noeud_t n, int weight, int height, int colonnes) {
    int valeur;
    cellule_t * cell;
    cell = malloc(sizeof(cellule_t));
    valeur = n.valeur;
    if(cell){
        cell->noeud = n;
        cell->w = weight;
        cell->h = height;
        cell->i = valeur/colonnes;
        cell->j = valeur%colonnes;
        cell->wall = 0;
    }
    return cell;
}

void drawCell(SDL_Renderer * renderer, cellule_t * cell){
    SDL_Point points[4];
    points[0].x = cell->j * cell->w;
    points[0].y = cell->i * cell->h;
    points[1].x = cell->j * cell->w + cell->w;
    points[1].y = cell->i * cell->h;
    points[2].x = cell->j * cell->w;
    points[2].y = cell->i * cell->h + cell->h;
    points[3].x = cell->j * cell->w + cell->w;
    points[3].y = cell->i * cell->h + cell->h;
    printf("%d = %d\n", cell->noeud.valeur, cell->wall);
    if(!(cell->wall & 0b00000001)){
        drawWall(renderer, points[0], points[1]);
    }
    if(!(cell->wall & 0b00000010)){
        drawWall(renderer, points[2], points[3]);
    }
    if(!(cell->wall & 0b00000100)){
        drawWall(renderer, points[1], points[3]);
    }
    if(!(cell->wall & 0b00001000)){
        drawWall(renderer, points[0], points[2]);
    }
}

void drawWall(SDL_Renderer * renderer, SDL_Point p1, SDL_Point p2){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}


void orientiation(cellule_t ** cell1, cellule_t ** cell2, int colonnes){
	int i,j,x,y;
	i = (*cell1)->noeud.valeur/colonnes;
	j = (*cell1)->noeud.valeur%colonnes;
	x = (*cell2)->noeud.valeur/colonnes;
	y = (*cell1)->noeud.valeur%colonnes;

	if (i == x) {
		(*cell1)->wall+=2;
		(*cell2)->wall+=1;
	}
	if(j == y){
		(*cell1)->wall+=4;
		(*cell2)->wall+=8;
	}
}

