#include "../headers/graphics.h"

void initGraphics() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
}

SDL_Window *createWindow(int xPos, int yPos, int width, int height) {
    SDL_Window *window = SDL_CreateWindow("WIFI", xPos, yPos, width, height, 0);
    if (window == NULL) {
        endSdl(0, "Erreur dans la creation de la fenetre", window, NULL);
    }

    return window;
}

SDL_Renderer *createRenderer(SDL_Window *window) {
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        endSdl(0, "Erreur dans la création du renderer", window, renderer);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    return renderer;
}

void endSdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer) {
    char msg_formated[255];
    int l;

    if (!ok) {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL) SDL_DestroyRenderer(renderer);
    if (window != NULL) SDL_DestroyWindow(window);

    SDL_Quit();
    IMG_Quit();
    if (!ok) {
        exit(EXIT_FAILURE);
    }
}

