#include "../headers/graph.h"
#include "../headers/labyrinthe.h"
#include "../headers/graphics.h"
#include "../headers/cellule.h"
#include <time.h>
#define LIGNE 10
#define COLONNE 10
#define SEED 42

int main() {
    int tailleCellW,tailleCellH;
    SDL_DisplayMode disp;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int i = 0;
    cellule_t * cell;
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    window = createWindow(500, 10, WINDOW_W, WINDOW_H);
    renderer = createRenderer(window);
    srand(SEED);
	labyrinthe_t * labyrinthe = creerLabyrintheQqc(LIGNE, COLONNE, 0.5);
	generateGraphvizGraph(labyrinthe->graphe, "graphe_FYP");
	tailleCellH = WINDOW_H/COLONNE;
	tailleCellW = WINDOW_W/LIGNE;
    SDL_bool program_on = SDL_TRUE;
    while (program_on) {
        SDL_Event event;
        if(i < labyrinthe->graphe->listeAretes->tailleCourante){
            cell = creerCelluleDepuisNoeud(labyrinthe->graphe->listeAretes->array[i]->n1,tailleCellW,tailleCellH,COLONNE);
            drawCell(renderer,cell);
            free(cell);
            cell = creerCelluleDepuisNoeud(labyrinthe->graphe->listeAretes->array[i]->n2,tailleCellW,tailleCellH,COLONNE);
            drawCell(renderer,cell);
            free(cell);
		i++;
        }

        while (program_on && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
	libererLabyrinthe(labyrinthe);
}
