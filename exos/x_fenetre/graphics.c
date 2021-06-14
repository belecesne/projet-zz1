#include "graphics.h"

void initGraphics() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
}

SDL_Window * creerFenetre(int xPos, int yPos, int width, int height) {
    SDL_Window * window = SDL_CreateWindow("SDL Window", xPos, yPos, width, height, SDL_WINDOW_RESIZABLE);  
    if (window_1 == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return window;
}