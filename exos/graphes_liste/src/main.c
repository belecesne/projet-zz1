#include "../headers/graph.h"
#include "../headers/labyrinthe.h"
#include "../headers/graphics.h"
#include "../headers/cellule.h"
#include "../headers/dikstra.h"
#include "../headers/draw_parcours.h"
#include "../headers/file.h"
#include <time.h>

#define LIGNE 10
#define COLONNE 10
#define SEED 42

int main() {
    int tailleCellW, tailleCellH, enParcours = 0;
    file_t * fileParcours;
    SDL_DisplayMode disp;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *textureMur, *textureSol, *textureSortie, *textureEntree;
    int window_w, window_h;
    tailleCellH = (WINDOW_H / (LIGNE * 2 + 1));
    tailleCellW = (WINDOW_W / (COLONNE * 2 + 1));
    window_w = (tailleCellW) * (COLONNE * 2 + 1);
    window_h = (tailleCellH) * (LIGNE * 2 + 1);
    printf("%d - %d\n", window_w, window_h);
    srand(SEED);
    labyrinthe_t *labyrinthe = creerLabyrintheQqc(LIGNE, COLONNE, tailleCellW, tailleCellH, 0.05);
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    window = createWindow(10, 10, window_w, window_h);
    renderer = createRenderer(window);
    textureMur = IMG_LoadTexture(renderer, "data/wall.png");
    textureSol = IMG_LoadTexture(renderer, "data/ground.png");
    textureEntree = IMG_LoadTexture(renderer, "data/entree.png");
    textureSortie = IMG_LoadTexture(renderer, "data/sortie.png");
    printf("Entree : %d - Sortie : %d", labyrinthe->entree, labyrinthe->sortie);
    SDL_bool program_on = SDL_TRUE;

    while (program_on) {
        SDL_Event event;
        SDL_RenderClear(renderer);
        drawLabyrinthe(renderer, labyrinthe, window_w, window_h, textureMur,
                       textureSol, textureEntree, textureSortie);
        if(enParcours){
            if(file_est_vide(file){
                enParcours = 0;
            } else {
                switch(enParcours){
                    case 1:
                        drawDijkstra(file);
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    default:
                        break;
                }
            }
        }
        while (program_on && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                case SDLK_d:
                    if(!enParcours){
                        enParcours = 1;
                        file = dikstra(labyrinthe->graphe, labyrinthe->entree, labyrinthe->sortie);
                    }
                    break;
                case SDLK_a:
                    if(!enParcours){
                        enParcours = 2;
                        
                    }
                    break;
                case SDLK_p:
                    if(!enParcours){
                        enParcours = 3;
                        
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    SDL_DestroyTexture(textureSol);
    SDL_DestroyTexture(textureMur);
    SDL_DestroyTexture(textureEntree);
    SDL_DestroyTexture(textureSortie);
    endSdl(1, "Fermeture Normale", window, renderer);
    libererLabyrinthe(labyrinthe);
}
