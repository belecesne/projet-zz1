#include "../headers/graph.h"
#include "../headers/labyrinthe.h"
#include "../headers/graphics.h"
#include "../headers/cellule.h"
#include <time.h>
#define LIGNE 10
#define COLONNE 10
#define SEED 42

int main() {
    int tailleCellW,tailleCellH, window_h, window_w;
    SDL_DisplayMode disp;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int i = 0;
	tailleCellH = (WINDOW_H / (LIGNE + 1));
	tailleCellW = (WINDOW_W / (COLONNE + 1));
	window_w = (tailleCellW) * (COLONNE+ 1);
	window_h = (tailleCellH) * (LIGNE+ 1);

	cellule_t * cell;
    srand(SEED);
	labyrinthe_t * labyrinthe = creerLabyrintheQqc(LIGNE, COLONNE, tailleCellW, tailleCellH);
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    window = createWindow(10, 10, window_w, window_h);
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
