#include "../headers/main.h"

int main(int *argc, char *argv[]) {
	SDL_DisplayMode disp;
	SDL_Window * window;
	SDL_Renderer * renderer;
	initGraphics();
	SDL_GetCurrentDisplayMode(0, &disp);
	window = createWindow(100, 100, 500, 500);
	renderer = createRenderer(window);

	SDL_Texture * sprite = IMG_LoadTexture(renderer, './data/stripe_player.png');
	SDL_Rect * frames = loadAnimationPos(2, 8, 150, 50),  dest = {0, 200, 0, 0};
	int i = 0, currentFrame = 0;
	while(i < 1000000){
		SDL_RenderClear(renderer);
		drawOneFrame(frames, sprite, renderer, currentFrame, dest, 0);
		currentFrame = (currentFrame + 1) % 8;
		SDL_RenderPresent(renderer);
		SDL_Delay(100);
		i++;
	}

	endSdl(1, "Fermeture Normale", window, renderer);
	return 0;
}