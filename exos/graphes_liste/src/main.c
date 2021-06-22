#include "../headers/graph.h"
#include "../headers/maillon_arete.h"
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
    arete_t * arete;
    maillon_arete_t * areteCourante;
    cellule_t * cell;
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    window = createWindow(500, 10, WINDOW_W, WINDOW_H);
    renderer = createRenderer(window);
    srand(SEED);
	labyrinthe_t * labyrinthe = creerLabyrintheQqc(LIGNE, COLONNE,0.5);
	generateGraphvizGraph(labyrinthe->graphe, "graphe_FYP");
	tailleCellH = WINDOW_H/COLONNE;
	tailleCellW = WINDOW_W/LIGNE;
    SDL_bool program_on = SDL_TRUE;
    areteCourante = labyrinthe->graphe->listeAretes;
    while (program_on) {
        SDL_Event event;
        if(areteCourante){
            cell = creerCelluleDepuisNoeud(areteCourante->arete->n1,tailleCellW,tailleCellH,COLONNE);
            drawCell(renderer,cell);
            free(cell);
            cell = creerCelluleDepuisNoeud(areteCourante->arete->n2,tailleCellW,tailleCellH,COLONNE);
            drawCell(renderer,cell);
            free(cell);
            areteCourante = areteCourante->suivant;
        }
        SDL_RenderPresent(renderer);

        while (program_on && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
        SDL_Delay(100);
    }
	liberer_graphe(labyrinthe->graphe);
	free(labyrinthe);
}