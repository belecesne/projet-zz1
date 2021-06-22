#include "../headers/cellule.h"

cellule_t *creerCelluleDepuisNoeud(noeud_t n, int weight, int height, int colonnes) {
    int valeur;
    cellule_t *cell;
    cell = malloc(sizeof(cellule_t));
    valeur = n.valeur;
    if (cell) {
        cell->noeud.valeur = n.valeur;
        cell->w = weight;
        cell->h = height;
        cell->i = valeur / colonnes;
        cell->j = valeur % colonnes;
        cell->wall = 0;
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

void drawCellText(SDL_Renderer *renderer, cellule_t *cell, SDL_Texture *textureMur, SDL_Texture *textureSol) {
    SDL_Point points[4];
    points[0].x = (cell->j * cell->w) * 2 + cell->w;
    points[0].y = (cell->i * cell->h) * 2 + cell->h;
    SDL_Point pointMur;
    if (!(cell->wall & 0b00000001)) {
        pointMur.x = points[0].x;
        pointMur.y = points[0].y - cell->h;
        drawText(renderer, pointMur, cell->h, cell->w, textureMur);
    }
    if (!(cell->wall & 0b00000010)) {
        pointMur.x = points[0].x;
        pointMur.y = points[0].y + cell->h;
        drawText(renderer, pointMur, cell->h, cell->w, textureMur);

    }
    if (!(cell->wall & 0b00000100)) {
        pointMur.x = points[0].x + cell->w;
        pointMur.y = points[0].y;
        drawText(renderer, pointMur, cell->h, cell->w, textureMur);

    }
    if (!(cell->wall & 0b00001000)) {
        pointMur.x = points[0].x - cell->w;
        pointMur.y = points[0].y;
        drawText(renderer, pointMur, cell->h, cell->w, textureMur);
    }
    drawText(renderer,points[0], cell->h, cell->w, textureSol);
}

void drawBack(SDL_Renderer *renderer, int window_w, int window_h, int wCell, int hCell, SDL_Texture *textureMur,SDL_Texture *textureSol) {
    SDL_Point p;
    for (int i = 0; i * hCell < window_h; i += 1) {
        for (int j = 0; j * wCell < window_w; j += 1) {
            p.x = j * wCell;
            p.y = i * hCell;
            drawText(renderer, p, hCell, wCell, textureSol);
        }
    }
    for (int i = 0; i * hCell < window_h; i += 2) {
        for (int j = 0; j * wCell < window_w; j += 2) {
            p.x = j * wCell;
            p.y = i * hCell;
            drawText(renderer, p, hCell, wCell, textureMur);
        }
    }
}

void drawText(SDL_Renderer *renderer, SDL_Point p1, int h, int w, SDL_Texture *texture) {

    SDL_Rect source = {0};
    SDL_Rect destination = {p1.x, p1.y, w, h};

    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);
    SDL_RenderCopy(renderer, texture, &source, &destination);
}
