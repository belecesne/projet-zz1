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
	liberer_graphe(labyrinthe->graphe);
	free(labyrinthe);
}