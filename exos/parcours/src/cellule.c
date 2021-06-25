#include "../headers/cellule.h"

cellule_t *creerCelluleDepuisNoeud(noeud_t n, int weight, int height, int colonnes) {
    int valeur;
    cellule_t *cell;
    cell = malloc(sizeof(cellule_t));
    valeur = n;
    if (cell) {
        cell->noeud = n;
        cell->w = weight;
        cell->h = height;
        cell->i = valeur / colonnes;
        cell->j = valeur % colonnes;
        cell->wall = 0;
        cell->etat = 0;
    }
    return cell;
}

void drawCell(SDL_Renderer *renderer, cellule_t *cell) {
    SDL_Point points[4];
    points[0].x = (cell->j * cell->w) * 2;
    points[0].y = (cell->i * cell->h) * 2;
    points[1].x = (cell->j * cell->w) * 2 + cell->w;
    points[1].y = (cell->i * cell->h) * 2;
    points[2].x = (cell->j * cell->w) * 2;
    points[2].y = (cell->i * cell->h) * 2 + cell->h;
    points[3].x = (cell->j * cell->w) * 2 + cell->w;
    points[3].y = (cell->i * cell->h) * 2 + cell->h;
    if (!(cell->wall & 0b00000001)) {
        drawWall(renderer, points[0], points[1]);
    }
    if (!(cell->wall & 0b00000010)) {
        drawWall(renderer, points[2], points[3]);
    }
    if (!(cell->wall & 0b00000100)) {
        drawWall(renderer, points[1], points[3]);
    }
    if (!(cell->wall & 0b00001000)) {
        drawWall(renderer, points[0], points[2]);
    }
}

void drawWall(SDL_Renderer *renderer, SDL_Point p1, SDL_Point p2) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void drawCellText(SDL_Renderer *renderer, cellule_t *cell, SDL_Texture *textureMur, SDL_Texture *textureSol, SDL_Texture * textureSolGris) {
	SDL_Point point;
	SDL_Rect rect;
	SDL_Point pointMur;
	SDL_Point pointVoisin;
	point.x = (cell->j * cell->w) * 2 + cell->w;
	point.y = (cell->i * cell->h) * 2 + cell->h;
	rect.w = cell->w;
	rect.h = cell->h;
	drawText(renderer, point, cell->w, cell->h, textureSol);
	if (!(cell->wall & 0b00000001)) {
		pointMur.x = point.x;
		pointMur.y = point.y - cell->h;
		drawText(renderer, pointMur, cell->w, cell->h, textureMur);
	} else if(cell->etat == 2){
		pointVoisin.x = point.x;
		pointVoisin.y = point.y - cell->h;
		drawText(renderer, pointVoisin, cell->w, cell->h, textureSolGris);
	}
	if (!(cell->wall & 0b00000010)) {
		pointMur.x = point.x;
		pointMur.y = point.y + cell->h;
		drawText(renderer, pointMur, cell->w, cell->h, textureMur);
	} else if(cell->etat == 2){
		pointVoisin.x = point.x;
		pointVoisin.y = point.y + cell->h;
		drawText(renderer, pointVoisin, cell->w, cell->h, textureSolGris);
	}
	if (!(cell->wall & 0b00000100)) {
		pointMur.x = point.x + cell->w;
		pointMur.y = point.y;
		drawText(renderer, pointMur, cell->w, cell->h, textureMur);
	} else if(cell->etat == 2){
		pointVoisin.x = point.x + cell->w;
		pointVoisin.y = point.y;
		drawText(renderer, pointVoisin, cell->w, cell->h, textureSolGris);
	}
	if (!(cell->wall & 0b00001000)) {
		pointMur.x = point.x - cell->w;
		pointMur.y = point.y;
		drawText(renderer, pointMur, cell->w, cell->h, textureMur);
	} else if(cell->etat == 2){
		pointVoisin.x = point.x - cell->w;
		pointVoisin.y = point.y;
		drawText(renderer, pointVoisin, cell->w, cell->h, textureSolGris);
	}
	if(cell->etat == 1){
		rect.x = point.x;
		rect.y = point.y;
		SDL_SetRenderDrawColor(renderer, 0, 200, 0, 100);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	else if(cell->etat == 2){
		drawText(renderer, point, cell->w, cell->h, textureSolGris);
	}
}
void drawBack(SDL_Renderer *renderer, int window_w, int window_h, int wCell, int hCell, SDL_Texture *textureMur,
              SDL_Texture *textureSol) {
    SDL_Point p;
    for (int i = 0; i * hCell < window_h; i += 1) {
        for (int j = 0; j * wCell < window_w; j += 1) {
            p.x = j * wCell;
            p.y = i * hCell;
            drawText(renderer, p, wCell, hCell, textureSol);
        }
    }
    for (int i = 0; i * hCell < window_h; i += 2) {
        for (int j = 0; j * wCell < window_w; j += 2) {
            p.x = j * wCell;
            p.y = i * hCell;
            drawText(renderer, p, wCell, hCell, textureMur);
        }
    }
}

void drawText(SDL_Renderer *renderer, SDL_Point p1, int w, int h, SDL_Texture *texture) {

    SDL_Rect source = {0};
    SDL_Rect destination = {p1.x, p1.y, w, h};

    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);
    SDL_RenderCopy(renderer, texture, &source, &destination);
}

void drawEntree(SDL_Renderer *renderer, cellule_t *cell, SDL_Texture *texture) {
    SDL_Point p;
    p.x = (cell->j * cell->w) * 2 + cell->w;
    p.y = (cell->i * cell->h) * 2 + cell->h;
    drawText(renderer, p, cell->w, cell->h, texture);
}

void colorierVoisins(SDL_Renderer *renderer, cellule_t *cell, cellule_t **tabCellules, int colonnes) {
    int i, j, x, y;
    noeud_t n;
    SDL_Rect rect;
    rect.w = cell->w;
    rect.h = cell->h;
    SDL_Point point;
    point.x = (cell->j * cell->w) * 2 + cell->w;
    point.y = (cell->i * cell->h) * 2 + cell->h;
    i = cell->i;
    j = cell->j;

    if ((cell->wall & 0b00000001)) {
        x = i - 1;
        y = j;
        n = x * colonnes + y;
        if (tabCellules[n]->etat == 0) {
            tabCellules[n]->etat = 1;
            rect.x = point.x;
            rect.y = point.y - cell->h;
            SDL_SetRenderDrawColor(renderer, 0, 200, 0, 100);
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
    }
    if ((cell->wall & 0b00000010)) {
        x = i + 1;
        y = j;
        n = x * colonnes + y;
        if (tabCellules[n]->etat == 0) {
            tabCellules[n]->etat = 1;
            rect.x = point.x;
            rect.y = point.y + cell->h;
            SDL_SetRenderDrawColor(renderer, 0, 200, 0, 100);
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
    }
    if ((cell->wall & 0b00000100)) {
        x = i;
        y = j + 1;
        n = x * colonnes + y;
        if (tabCellules[n]->etat == 0) {
            tabCellules[n]->etat = 1;
            rect.x = point.x + cell->w;
            rect.y = point.y;
            SDL_SetRenderDrawColor(renderer, 0, 200, 0, 100);
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
    }
    if ((cell->wall & 0b00001000)) {
        x = i;
        y = j - 1;
        n = x * colonnes + y;
        if (tabCellules[n]->etat == 0) {
            tabCellules[n]->etat = 1;
            rect.x = point.x - cell->w;
            rect.y = point.y;
            SDL_SetRenderDrawColor(renderer, 0, 200, 0, 100);
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
    }

}
