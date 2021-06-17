#include "../headers/main.h"


int main(int argc, char *argv[]) {
	SDL_DisplayMode disp;
	SDL_Window *window;
	SDL_Texture *texture[7];
	SDL_Renderer *renderer;
	int yDVD1H, yDVD2H, xDVD1W, xDVD2W, xDVD1, xDVD2, dx, dy, yDVD1, yDVD2, x1, y1, prev;
	int drawed = 0;
	initGraphics();
	SDL_GetCurrentDisplayMode(0, &disp);
	window = createWindow(960 - WINDOW_W / 2, 540 - WINDOW_H / 2, WINDOW_W, WINDOW_H);
	renderer = createRenderer(window);
	srand(time(NULL));


	xDVD1 = (rand() % WINDOW_W), yDVD1 = (rand() % WINDOW_H);
	xDVD2 = (rand() % WINDOW_W), yDVD2 = (rand() % WINDOW_H);
	x1 = xDVD1;
	y1 = yDVD1;

	yDVD1H = yDVD1 + DVDSIZE_H;
	yDVD2H = yDVD2 + DVDSIZE_H;
	xDVD1W = xDVD1 + DVDSIZE_W;
	xDVD2W = xDVD2 + DVDSIZE_W;
	dx = rand() % 2;
	dy = rand() % 2;
	if (dx == 0) {
		dx = -1;
	}
	if (dy == 0) {
		dy = -1;
	}

	dvd_t dvd1 = {{{xDVD1, yDVD1}, {xDVD1W, yDVD1H}}, SPEED, SPEED, dx, dy, (rand() % 7), 0, 50};

	dx = rand() % 2;
	dy = rand() % 2;
	if (dx == 0) {
		dx = -1;
	}
	if (dy == 0) {
		dy = -1;
	}
	dvd_t dvd2 = {{{xDVD2, yDVD2}, {xDVD2W, yDVD2H}}, SPEED, SPEED, dx, dy, (rand() % 7), 0, 20};

	texture[0] = IMG_LoadTexture(renderer, "data/dvd_blanc.png");
	texture[1] = IMG_LoadTexture(renderer, "data/dvd_bleu.png");
	texture[2] = IMG_LoadTexture(renderer, "data/dvd_jaune.png");
	texture[3] = IMG_LoadTexture(renderer, "data/dvd_orange.png");
	texture[4] = IMG_LoadTexture(renderer, "data/dvd_rose.png");
	texture[5] = IMG_LoadTexture(renderer, "data/dvd_rouge.png");
	texture[6] = IMG_LoadTexture(renderer, "data/dvd_vert.png");


	completeArray();


	if (x1 - BALL_RADIUS < 0) {
		x1 += BALL_RADIUS * 2;
	} else if (WINDOW_W - BALL_RADIUS <= x1) {
		x1 -= BALL_RADIUS * 2;
	}
	if (y1 - BALL_RADIUS < 0) {
		y1 += BALL_RADIUS * 2;
	} else if (WINDOW_H - BALL_RADIUS <= y1) {
		y1 -= BALL_RADIUS * 2;
	}

	if (dvd1.coo[0].x < DVDSIZE_W) {
		dvd1.coo[0].x += DVDSIZE_W;
	} else if (dvd1.coo[0].x > WINDOW_W - DVDSIZE_W) {
		dvd1.coo[0].x -= DVDSIZE_W;
	}
	if (dvd1.coo[0].y < DVDSIZE_H) {
		dvd1.coo[0].y += DVDSIZE_H;
	} else if (dvd1.coo[0].y > WINDOW_H - DVDSIZE_H) {
		dvd1.coo[0].y -= DVDSIZE_H;
	}

	if (dvd2.coo[0].x < DVDSIZE_W) {
		dvd2.coo[0].x += DVDSIZE_W;
	} else if (dvd2.coo[0].x > WINDOW_W - DVDSIZE_W) {
		dvd2.coo[0].x -= DVDSIZE_W;
	}
	if (dvd2.coo[0].y < DVDSIZE_H) {
		dvd2.coo[0].y += DVDSIZE_H;
	} else if (dvd2.coo[0].y > WINDOW_H - DVDSIZE_H) {
		dvd2.coo[0].y -= DVDSIZE_H;
	}


	SDL_bool program_on = SDL_TRUE;
	while (program_on) {
		SDL_Event event;
		if (drawed == 1) {
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_W]) {
				prev = dvd1.dy;
				dvd1.dy = -1;
				dvd1.coo[0].y += dvd1.precSpeed * dvd1.dy;
				dvd1.dy = prev;
			} else if (state[SDL_SCANCODE_A]) {
				prev = dvd1.dx;
				dvd1.dx = -1;
				dvd1.coo[0].x += dvd1.precSpeed * dvd1.dx;
				dvd1.dx = prev;
			} else if (state[SDL_SCANCODE_S]) {
				prev = dvd1.dy;
				dvd1.dy = 1;
				dvd1.coo[0].y += dvd1.precSpeed * dvd1.dy;
				dvd1.dy = prev;

			} else if (state[SDL_SCANCODE_D]) {
				prev = dvd1.dx;
				dvd1.dx = 1;
				dvd1.coo[0].x += dvd1.precSpeed * dvd1.dx;
				dvd1.dx = prev;

			}

			if (state[SDL_SCANCODE_UP]) {
				prev = dvd1.dy;
				dvd2.dy = -1;
				dvd2.coo[0].y += dvd2.precSpeed * dvd2.dy;
				dvd1.dy = prev;
			} else if (state[SDL_SCANCODE_LEFT]) {
				prev = dvd1.dx;
				dvd2.dx = -1;
				dvd2.coo[0].x += dvd2.precSpeed * dvd2.dx;
				dvd1.dx = prev;
			} else if (state[SDL_SCANCODE_DOWN]) {
				prev = dvd1.dy;
				dvd2.dy = 1;
				dvd2.coo[0].y += dvd2.precSpeed * dvd2.dy;
				dvd1.dy = prev;
			} else if (state[SDL_SCANCODE_RIGHT]) {
				prev = dvd1.dx;
				dvd2.dx = 1;
				dvd2.coo[0].x += dvd2.precSpeed * dvd2.dx;
				dvd1.dx = prev;
			}
		}
		while (program_on && SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT :
					program_on = SDL_FALSE;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_SPACE:
							if (drawed == 1) {

								if (dvd1.speed) {
									dvd1.precSpeed = dvd1.speed;
									dvd2.precSpeed = dvd2.speed;
									dvd1.speed = 0;
									dvd2.speed = 0;
								} else {
									dvd1.speed = dvd1.precSpeed;
									dvd2.speed = dvd2.precSpeed;
								}
							}
							break;
						case SDLK_RETURN:
							drawed = (drawed + 1) % 2;
							break;
					}
					break;

				default:
					break;
			}

		}


		SDL_RenderClear(renderer);
		switch (drawed) {
			case 0:
				drawBall(renderer, x1, y1, BALL_RADIUS);
				SDL_RenderPresent(renderer);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				if (x1 + dx > WINDOW_W - BALL_RADIUS || x1 + dx < BALL_RADIUS) {
					dx = -dx;
				}
				if (y1 + dy > WINDOW_H - BALL_RADIUS || y1 + dy < BALL_RADIUS) {
					dy = -dy;
				}
				x1 += SPEED * dx;
				y1 += SPEED * dy;

				break;
			case 1:{
				if(dvd2.coo[0].y >= dvd1.coo[0].y - DVDSIZE_H && dvd2.coo[0].y <= dvd1.coo[1].y){
					if((dvd2.coo[0].x >= dvd1.coo[1].x - 1 && dvd2.coo[0].x <= dvd1.coo[1].x + 1) ||
					   (dvd1.coo[0].x >= dvd2.coo[1].x - 1 && dvd1.coo[0].x <= dvd2.coo[1].x + 1)){
						dvd1.dx = -dvd1.dx;
						dvd2.dx = -dvd2.dx;
					}
				}

				if(dvd2.coo[0].x >= dvd1.coo[0].x - DVDSIZE_W && dvd2.coo[0].x <= dvd1.coo[1].x){
					if((dvd2.coo[0].y >= dvd1.coo[1].y - 1 && dvd2.coo[0].y <= dvd1.coo[1].y + 1) ||
					   (dvd1.coo[0].y >= dvd2.coo[1].y - 1 && dvd1.coo[0].y <= dvd2.coo[1].y + 1)){
						dvd1.dy = -dvd1.dy;
						dvd2.dy = -dvd2.dy;
					}
				}

				drawDVD(renderer, texture[dvd1.currText], dvd1.coo[0].x, dvd1.coo[0].y);
				drawDVD(renderer, texture[dvd2.currText], dvd2.coo[0].x, dvd2.coo[0].y);
				SDL_RenderPresent(renderer);


				// DVD 1
				if(dvd1.coo[0].x + dvd1.dx > WINDOW_W - DVDSIZE_W || dvd1.coo[0].x + dvd1.dx < 0){
					dvd1.dx = -dvd1.dx;
					dvd1.prevText = dvd1.currText;
					while(dvd1.prevText == dvd1.currText){
						dvd1.currText = (rand() % 7);
					}
					if(dvd1.dx > 0){
						moveWindowLeft(window, dvd1.windowMovingSpeed);
					} else{
						moveWindowRight(window, disp, dvd1.windowMovingSpeed);
					}
				}
				if(dvd1.coo[0].y + dvd1.dy > WINDOW_H - DVDSIZE_H || dvd1.coo[0].y + dvd1.dy < 0){
					dvd1.dy = -dvd1.dy;
					dvd1.prevText = dvd1.currText;
					while(dvd1.prevText == dvd1.currText){
						dvd1.currText = (rand() % 7);
					}
					if(dvd1.dy > 0){
						moveWindowUp(window, dvd2.windowMovingSpeed);

					} else{
						moveWindowDown(window, disp, dvd2.windowMovingSpeed);
					}

				}
				// DVD 2
				if(dvd2.coo[0].x + dvd2.dx > WINDOW_W - DVDSIZE_W || dvd2.coo[0].x + dvd2.dx < 0){
					dvd2.dx = -dvd2.dx;
					dvd2.prevText = dvd2.currText;
					while(dvd2.prevText == dvd2.currText){
						dvd2.currText = (rand() % 7);
					}
					if(dvd2.dx > 0){
						moveWindowLeft(window, dvd2.windowMovingSpeed);
					} else{
						moveWindowRight(window, disp, dvd2.windowMovingSpeed);
					}

				}
				if(dvd2.coo[0].y + dvd2.dy > WINDOW_H - DVDSIZE_H || dvd2.coo[0].y + dvd2.dy < 0){
					dvd2.dy = -dvd2.dy;
					dvd2.prevText = dvd2.currText;
					while(dvd2.prevText == dvd2.currText){
						dvd2.currText = (rand() % 7);
					}
					if(dvd2.dy > 0){
						moveWindowUp(window, dvd2.windowMovingSpeed);

					} else{
						moveWindowDown(window, disp, dvd2.windowMovingSpeed);
					}
				}
				dvd1.coo[0].x += dvd1.speed * dvd1.dx;
				dvd1.coo[0].y += dvd1.speed * dvd1.dy;
				dvd2.coo[0].x += dvd2.speed * dvd2.dx;
				dvd2.coo[0].y += dvd2.speed * dvd2.dy;

				dvd1.coo[1].x = dvd1.coo[0].x + DVDSIZE_W;
				dvd1.coo[1].y = dvd1.coo[0].y + DVDSIZE_H;
				dvd2.coo[1].x = dvd2.coo[0].x + DVDSIZE_W;
				dvd2.coo[1].y = dvd2.coo[0].y + DVDSIZE_H;
				break;
			}
		}


		// COLLISIONS




		SDL_Delay(5);
	}

	for (
			int i = 0;
			i < 7; i++) {
		SDL_DestroyTexture(texture[i]);
	}
	endSdl(1, "Fermeture Normale", window, renderer);
	return 0;
}