#include "../headers/main.h"


int main(int argc, char* argv[]){
	srand(time(NULL));

	SDL_DisplayMode disp;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect sourceBg = {0}, destBg = {0}, posScore = {300, 0, 150, 50}, posEnd = {100, 100, 100, 50};

	initGraphics();
	SDL_GetCurrentDisplayMode(0, &disp);
	window = createWindow(10, 10, WINDOW_W, WINDOW_H);
	renderer = createRenderer(window);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	char scoreString[15];
	if(TTF_Init() < 0){
		endSdl(0, "Erreur dans l'init de TTF", window, renderer);
	}
	TTF_Font* font = NULL, * fontEnd = NULL;
	font = TTF_OpenFont("./data/asianninja.ttf", 25);
	if(font == NULL){
		endSdl(0, "Erreur dans l'ouverture de la police", window, renderer);
	}
	fontEnd = TTF_OpenFont("./data/asianninja.ttf", 50);
	if(fontEnd == NULL){
		endSdl(0, "Erreur dans l'ouverture de la police", window, renderer);
	}
	SDL_Color color = {0, 0, 0, 255};
	SDL_Surface* textSurface = NULL, *endSurface = NULL;
	SDL_Texture* textTexture = NULL, *endTexture = NULL;

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

	int i = 0;
	int currentFrameRun = 0, currentFrameIdle = 0, currentFrameJump = 0, flipped = 0, jumpDelay = 0, score = 0, coll = 1, lose = 0;

	SDL_Point coordArray[7] = {{0,   100},
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
		if(lose){
			SDL_Rect rect = {0, 0, 450, 800};
			SDL_SetRenderDrawColor(renderer, 50, 50, 50, 100);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			posScore.x = 225 - posScore.w / 2;
			posScore.y = 450 - posScore.h / 2;
			endSurface = TTF_RenderText_Blended(fontEnd, "Perdu", color);
			endTexture = SDL_CreateTextureFromSurface(renderer, endSurface);
			if(endTexture == NULL){
				endSdl(0, "Impossible de cr??er la surface", window, renderer);
			}
			SDL_QueryTexture(endTexture, NULL, NULL, &posEnd.w, &posEnd.h);
			posEnd.x = 225 - posEnd.w / 2;
			posEnd.y = 400 - posEnd.h / 2;
			SDL_RenderCopy(renderer, endTexture, NULL, &posEnd);
		}
		sprintf(scoreString, "Score : %d", score);
		textSurface = TTF_RenderText_Blended(font, scoreString, color);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if(textTexture == NULL){
			endSdl(0, "Impossible de cr??er la surface", window, renderer);
		}
		SDL_QueryTexture(textTexture, NULL, NULL, &posScore.w, &posScore.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &posScore);
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if(state[SDL_SCANCODE_RIGHT] && !lose){
			flipped = 0;
			player.dx = DX;
			player.isMoving = 1;
			moveRight(WINDOW_W, &player);
			if(!player.isJumping && coll){
				drawOneFrame(framesRun, texture, renderer, currentFrameRun, &player, flipped);
				currentFrameRun = (currentFrameRun + 1) % 6;

			}
		} else if(state[SDL_SCANCODE_LEFT] && !lose){
			flipped = 1;
			player.dx = -DX;
			player.isMoving = 1;

			moveLeft(&player);
			if(!player.isJumping && coll){
				drawOneFrame(framesRun, texture, renderer, currentFrameRun, &player, flipped);
				currentFrameRun = (currentFrameRun + 1) % 6;

			}

		}
		if(state[SDL_SCANCODE_UP] && !lose){
			if(!player.isJumping && player.canJump){
				player.isJumping = 1;
				player.canJump = 0;
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
						case SDLK_q:
							program_on = SDL_FALSE;
							break;
						case SDLK_ESCAPE:
							program_on = SDL_FALSE;
							break;
						default:
							break;
					}
				default:
					break;
			}
		}

		// Animation statique
		if(!player.isMoving && !player.isJumping && coll){
			drawOneFrame(framesStatic, texture, renderer, currentFrameIdle, &player, flipped);
			i++;

			if(i == 4){
				currentFrameIdle = (currentFrameIdle + 1) % 5;
				i = 0;
			}
		}
		player.isMoving = 0;

		// Animation du saut
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

		// Gestion des collisions
		coll = collision(&player, coordArray);

		if(coll == 1){
			player.canJump = 1;
			player.isJumping = 0;
			player.jumpTime = 0;
			player.dy = 0;
		}
		if(coll == 2){
			coll = 1;
			player.canJump = 1;
			player.isJumping = 0;
			player.jumpTime = 0;
			player.dy = 0;
			nextPlatform(coordArray, window);
			player.rect.y += 100;
			currentFrameJump = 0;
			score++;
		}
		if(coll == 0){
			player.dy = 1;
			player.rect.y += JUMPSPEED * player.dy;
			drawOneFrame(framesJump, texture, renderer, 7, &player, flipped);
		}

		// Gestion de la d??faite
		if(player.rect.y >= WINDOW_H){
			lose = 1;
			coll = 1;
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(30);
	}
	TTF_Quit();
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(endSurface);
	SDL_DestroyTexture(plat1);
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(endTexture);
	endSdl(1, "Fermeture normale", window, renderer);
	return 0;
}
