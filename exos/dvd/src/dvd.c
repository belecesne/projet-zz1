#include "../headers/dvd.h"

static double COS[360];
static double SIN[360];

void completeArray() {
    double i = 0;
    int n = 0;
    while (n < 360) {
        COS[n] = cos(i);
        SIN[n] = sin(i);
        i += (M_PI / 180.0);
        n++;
    }
}

void drawCircle(SDL_Point *circle, int x, int y, int size) {

    int angle = 0;
    for (int i = 0; i < 40; i++, angle = (angle + 10) % 360) {
        circle[i].x = x - COS[angle] * size;
        circle[i].y = y - SIN[angle] * size;
        //printf("%d - %d / %lf - %lf\n",circle[i].x, circle[i].y,COS[angle],SIN[angle]);
    }
}

void drawBall(SDL_Renderer *renderer, int x, int y, int size) {
    SDL_Point circle[40];
    drawCircle(circle, x, y, size);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLines(renderer, circle, 40);
}

void drawDVD(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y) {
    SDL_Rect source = {0};
    SDL_Rect destination = {x, y, DVDSIZE_W, DVDSIZE_H};
    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);
    SDL_RenderCopy(renderer, texture, &source, &destination);
}

void moveWindowUp(SDL_Window *window, int speed) {
    int x, y, w, h;
    SDL_GetWindowPosition(window, &x, &y);
    SDL_GetWindowSize(window, &w, &h);
    if ((y - speed > 0)) {
        SDL_SetWindowPosition(window, x, y - speed);
    } else {
        SDL_SetWindowPosition(window, x, 0);
    }
}

void moveWindowDown(SDL_Window *window, SDL_DisplayMode disp,int speed) {
    int x, y, w, h;
    SDL_GetWindowPosition(window, &x, &y);
    SDL_GetWindowSize(window, &w, &h);
    if ((y + h + speed < disp.h)) {
        SDL_SetWindowPosition(window, x, y + speed);
    } else {
        SDL_SetWindowPosition(window, x, disp.h-h);
    }
}

void moveWindowRight(SDL_Window *window, SDL_DisplayMode disp,int speed) {
    int x, y, w, h;
    SDL_GetWindowPosition(window, &x, &y);
    SDL_GetWindowSize(window, &w, &h);
    if ((x + w + speed < disp.w)) {
        SDL_SetWindowPosition(window, x+speed, y);
    } else {
        SDL_SetWindowPosition(window, disp.w-w, y);
    }
}

void moveWindowLeft(SDL_Window *window,int speed) {
    int x, y, w, h;
    SDL_GetWindowPosition(window, &x, &y);
    SDL_GetWindowSize(window, &w, &h);
    if ((x + w - speed > 0)) {
        SDL_SetWindowPosition(window, x-speed, y);
    } else {
        SDL_SetWindowPosition(window, 0, y);
    }
}