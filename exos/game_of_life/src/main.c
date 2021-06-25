#include "../headers/graphics.h"
#include "../headers/game.h"
#include <string.h>

int main() {
    int survie[10] = {0, 0, 0, 1, 1, 0, 0, 0, 0, 0};
    int naissance[10] = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0};
    initGraphics();
    int game[GAME_LENGTH][GAME_LENGTH] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
{0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0},
{1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0},
{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
{1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0},
{0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0},
{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
{0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
{0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
{1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0}};
    SDL_Window * window = createWindow(0, 0, 640, 480);
    SDL_Renderer * renderer = createRenderer(window);

    drawMatrix(renderer, window, game, GAME_LENGTH);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    int copy[GAME_LENGTH][GAME_LENGTH];
	SDL_bool program_on = SDL_TRUE;
	int pause = 0;
	int mouseX = 0;
	int mouseY = 0;
	int chIndexI = 0;
	int chIndexJ = 0;
	int error = 0;
	int dragged = 0;
	while(program_on){
		SDL_Event event;
		if(dragged) {
			SDL_GetMouseState(&mouseX, &mouseY);
			error = getPosFromMouse(mouseX, mouseY, &chIndexI, &chIndexJ, window, GAME_LENGTH);
			if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && !error) {
				game[chIndexI][chIndexJ] = 0;
			}
			else if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT) && !error) {
				game[chIndexI][chIndexJ] = 1;
			}
		}
		if(!pause) {
			for(int i = 0; i < GAME_LENGTH && program_on; i++){
				for(int j = 0; j < GAME_LENGTH; j++){
					if(game[i][j]){
						applyRule(game, copy, GAME_LENGTH, survie, i, j);
					} else{
						applyRule(game, copy, GAME_LENGTH, naissance, i, j);
					}
				}
			}
			copyMatrix(copy, game, GAME_LENGTH);
			SDL_Delay(100);
		}
		drawMatrix(renderer, window, game, GAME_LENGTH);
		SDL_RenderPresent(renderer);
		while(program_on && SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					program_on = SDL_FALSE;
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_SPACE) {
						pause = !pause;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					dragged = 1;
					break;
				case SDL_MOUSEBUTTONUP:
					dragged = 0;
				default:
					break;
			}
		}
	}
    end_sdl(1, "Fin de la SDL", window, renderer);
}