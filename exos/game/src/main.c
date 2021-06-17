#include "../headers/main.h"


int main(int argc, char* argv[]){
	srand(time(NULL));

	SDL_DisplayMode disp;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect sourceBg = {0}, destBg = {0}, posScore = {300, 0, 150, 50};

	initGraphics();
	SDL_GetCurrentDisplayMode(0, &disp);
	window = createWindow(10, 10, WINDOW_W, WINDOW_H);
	renderer = createRenderer(window);
	char scoreString[15];
	if(TTF_Init() < 0){
		endSdl(0, "Erreur dans l'init de TTF", window, renderer);
	}
	TTF_Font* font = NULL;
	font = TTF_OpenFont("./data/asianninja.ttf", 25);
	if(font == NULL){
		endSdl(0, "Erreur dans l'ouverture de la police", window, renderer);
	}
	SDL_Color color = {0, 0, 0, 255};
	SDL_Surface* textSurface = NULL;
	SDL_Texture* textTexture = NULL;

	player_t player = {{25, 644, 100, 100}, DX, JUMPLENGTH, 0, 1, 1, 0};
	SDL_bool program_on = SDL_TRUE;
	SDL_Texture* plat1 = IMG_LoadTexture(renderer, "data/plat1.png");


	SDL_Texture* texture = IMG_LoadTexture(renderer, "./data/ninja.png");
	SDL_Texture* background = IMG_LoadTexture(renderer, "./data/asian_scene.png");
	SDL_Rect* framesJump = loadAnimationPos(2, 9, 300, 300);
	SDL_Rect* framesStatic = loadAnimationPos(0, 5, 300, 300);
	SDL_Rect* framesRun = loadAnimationPos(1, 6, 300, 300);
	SDL_QueryTexture(background, NULL, NULL, &sourceBg.w, &sourceBg.h);
	SDL_GetWindowSize(window, &destBg.w, &destBg.h);

	int i;
	int currentFrameRun = 0, currentFrameIdle = 0, currentFrameJump = 0, flipped = 0, win = 1, jumpDelay = 0, score = 0;

	SDL_Point coordArray[8] = {{0,   100},
	                           {150, 200},
	                           {300, 300},
	                           {0,   400},
	                           {150, 500},
	                           {300, 600},
	                           {0,   700}};
	while(program_on){
		SDL_Event event;
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background, &sourceBg, &destBg);
		createAllPlatforms(renderer, plat1, coordArray);
		sprintf(scoreString, "Score : %d", score);
		textSurface = TTF_RenderText_Blended(font, scoreString, color);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if(textTexture == NULL){
			endSdl(0, "Impossible de créer la surface", window, renderer);
		}
		SDL_QueryTexture(textTexture, NULL, NULL, &posScore.w, &posScore.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &posScore);
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if(state[SDL_SCANCODE_RIGHT]){
			flipped = 0;
			player.dx = DX;
			player.isMoving = 1;
			moveRight(WINDOW_W, &player);
			if(!player.isJumping && win){
				drawOneFrame(framesRun, texture, renderer, currentFrameRun, &player, flipped);
				currentFrameRun = (currentFrameRun + 1) % 6;

			}
		}
		if(state[SDL_SCANCODE_LEFT]){
			flipped = 1;
			player.dx = -DX;
			player.isMoving = 1;

			moveLeft(&player);
			if(!player.isJumping && win){
				drawOneFrame(framesRun, texture, renderer, currentFrameRun, &player, flipped);
				currentFrameRun = (currentFrameRun + 1) % 6;

			}

		}
		if(state[SDL_SCANCODE_UP]){
			if(!player.isJumping){
				player.isJumping = 1;
			}

		}
		while(program_on && SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT :
					program_on = SDL_FALSE;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_r:
							break;
						default:
							break;
					}
				default:
					break;
			}
		}


		if(!player.isMoving && win){
			if(!player.isJumping){
				drawOneFrame(framesStatic, texture, renderer, currentFrameIdle, &player, flipped);
			}
			i++;

			if(i == 6){
				currentFrameIdle = (currentFrameIdle + 1) % 5;
				i = 0;
			}
		}
		player.isMoving = 0;


		if(player.isJumping){
			if(player.jumpTime >= JUMPLENGTH){
				player.jumpTime = 0;
				player.dy = 0;
				player.isJumping = 0;

			} else{
				drawOneFrame(framesJump, texture, renderer, currentFrameJump, &player, flipped);
				if(jumpDelay == 2){
					currentFrameJump = (currentFrameJump + 1) % 9;
					jumpDelay = 0;
				}
				jumpDelay++;
				if(currentFrameJump == 7 && player.jumpTime <= JUMPLENGTH / 2){
					currentFrameJump = 3;
				} else if(player.jumpTime > JUMPLENGTH / 2){
					currentFrameJump = 7;
				}
				jump(&player);
			}
		}

		int coll = collision(&player, coordArray, WINDOW_H);
		if(coll == 0 || coll == 1){
			player.dy = 1;
			player.isJumping = 0;
			player.onPlatform = 1;
			player.jumpTime = 0;
			if(coll == 1){
				coll = 0;
				nextPlatform(coordArray, window);
				player.rect.y += 100;
				currentFrameJump = 0;
				score++;

			}

		}
		if(coll == -1){
			player.onPlatform = 0;
		}
		if(coll == -1 && !player.isJumping && !player.onPlatform){
			win = 0;
			player.dy = 1;
			player.rect.y += JUMPSPEED * player.dy;
			drawOneFrame(framesJump, texture, renderer, 7, &player, flipped);
			player.onPlatform = 0;
			printf("Defaite\n");
		}
		// Plateforme

		// Saut
		if(win == 0 && player.rect.y >= WINDOW_H){
			break;
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(30);
	}
	endSdl(1, "Fermeture normale", window, renderer);
	return 0;
}