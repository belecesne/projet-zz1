#include "../headers/graph.h"
#include "../headers/maillon_arete.h"
#include "../headers/labyrinthe.h"
#include "../headers/graphics.h"
#include <time.h>
#define LIGNE 4
#define COLONNE 4
#define SEED 42

int main() {
    SDL_DisplayMode disp;
    SDL_Window *window;
    SDL_Renderer *renderer;
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    window = createWindow(500, 10, WINDOW_W, WINDOW_H);
    renderer = createRenderer(window);
    srand(SEED);
	labyrinthe_t * labyrinthe = creerLabyrintheQqc(LIGNE, COLONNE,0.5);
	generateGraphvizGraph(labyrinthe->graphe, "graphe_FYP");
    SDL_bool program_on = SDL_TRUE;
    while (program_on) {
        SDL_Event event;
        while (program_on && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
        SDL_Delay(5);
    }
	liberer_graphe(labyrinthe->graphe);
	free(labyrinthe);
}