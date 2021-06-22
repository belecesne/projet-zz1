#include "../headers/graph.h"
#include "../headers/labyrinthe.h"
#include "../headers/graphics.h"
#include "../headers/cellule.h"
#include <time.h>
#define LIGNE 8
#define COLONNE 12
#define SEED 42

int main() {
    int tailleCellW,tailleCellH;
    SDL_DisplayMode disp;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture * textureMur, * textureSol;
    int i = 0, window_w, window_h;
	tailleCellH = (WINDOW_H/(LIGNE*2+1));
	tailleCellW = (WINDOW_W/(COLONNE*2+1));
	window_w = (tailleCellW)*(COLONNE*2+1);
    window_h = (tailleCellH)*(LIGNE*2+1);
    printf("%d - %d\n",window_w,window_h);
    cellule_t * cell;
    srand(SEED);
	labyrinthe_t * labyrinthe = creerLabyrintheQqc(LIGNE, COLONNE, tailleCellW, tailleCellH, 0.05);
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    window = createWindow(10, 10, window_w, window_h);
    renderer = createRenderer(window);
    textureMur = IMG_LoadTexture(renderer, "data/wall.png");
    textureSol = IMG_LoadTexture(renderer,"data/ground.png");
    SDL_bool program_on = SDL_TRUE;
    while (program_on) {
        SDL_Event event;
        SDL_RenderClear(renderer);
        drawBack(renderer,window_w,window_h,tailleCellW,tailleCellH,textureMur,textureSol);
        for(i = 0; i < labyrinthe->graphe->nbNoeuds; i++){
            cell = labyrinthe->tableauCellules[i];
            drawCellText(renderer,cell,textureMur,textureSol);
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
    SDL_DestroyTexture(textureSol);
    SDL_DestroyTexture(textureMur);
    endSdl(1, "Fermeture Normale", window, renderer);
    libererLabyrinthe(labyrinthe);
}
