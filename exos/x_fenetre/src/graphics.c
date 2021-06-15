#include "../headers/graphics.h"

void initGraphics() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
}

SDL_Window * createWindow(int xPos, int yPos, int width, int height) {
    SDL_Window * window = SDL_CreateWindow("SDL Window", xPos, yPos, width, height, SDL_WINDOW_RESIZABLE);  
    if (window == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return window;
}

SDL_Window ** createWindowMatrix(int length) {
    SDL_Window ** matrix = (SDL_Window**) calloc(length, sizeof(SDL_Window***));
    return matrix;
}

void initMatrix(SDL_Window ** matrix, int length, int screen_width, int screen_height) {
    int curr_x = 0;
    int curr_y = 0;
    const int window_x_size = (2 * screen_width) / length;
    const int window_y_size = (2 * screen_height) / length;
    for(int i = 0; i < length/2; i++) {
        matrix[i] = createWindow(curr_x, curr_y, window_x_size, window_y_size);
        curr_x += window_x_size;
        curr_y += window_y_size;
    }
    curr_x = screen_width - window_x_size;
    curr_y = 0;
    for(int i = length/2; i < length; i++) {
        if(matrix[i] == NULL) {
            matrix[i] = createWindow(curr_x, curr_y, window_x_size, window_y_size);
        }
        curr_x -= window_x_size;
        curr_y += window_y_size;
    }
}

void shiftWindows(SDL_Window** matrix, int length, int screen_width, int screen_height, int deltaTime, int shift) {
    int x, y, w, h = 0;
    int diffs = length;
    while(diffs != 0) {
        diffs = length;
        for(int i = 0; i < length; i++) {
            SDL_GetWindowPosition(matrix[i], &x, &y);
            SDL_GetWindowSize(matrix[i], &w, &h);
            if((x+w < screen_width) || (y+h < screen_height)) {
                SDL_SetWindowPosition(matrix[i], x+shift, y + shift);
            }
            else {
                diffs--;
            }
        }
        SDL_Delay(deltaTime);
    }
}

void destroyMatrix(SDL_Window** matrix, int length) {
    for(int i = 0; i < length; i++) {
        if(matrix[i] != NULL) {
            SDL_DestroyWindow(matrix[i]);
        }
    }
    free(matrix);
}
