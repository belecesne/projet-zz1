#include "../headers/graph.h"
#include "../headers/labyrinthe.h"
#include "../headers/graphics.h"
#include "../headers/cellule.h"
#include <time.h>
#define LIGNE 50
#define COLONNE 50
#define SEED 42

int main() {
    int tailleCellW,tailleCellH;
    SDL_DisplayMode disp;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int i = 0;
	tailleCellH = WINDOW_H/LIGNE;
	tailleCellW = WINDOW_W/COLONNE;
    cellule_t * cell;
    srand(SEED);
	labyrinthe_t * labyrinthe = creerLabyrintheQqc(LIGNE, COLONNE, tailleCellW, tailleCellH, 0.05);
	//generateGraphvizGraph(labyrinthe->graphe, "graphe_FYP");
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    window = createWindow(10, 10, WINDOW_W, WINDOW_H);
    renderer = createRenderer(window);

    SDL_bool program_on = SDL_TRUE;
    while (program_on) {
        SDL_Event event;
        SDL_RenderClear(renderer);
        for(i = 0; i < labyrinthe->graphe->nbNoeuds; i++){
            cell = labyrinthe->tableauCellules[i];
            drawCell(renderer,cell);
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
        SDL_Delay(2);
    }
	libererLabyrinthe(labyrinthe);
}
