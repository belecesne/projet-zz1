#include "../headers/snake.h"

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

void drawCircle(SDL_Point *circle, int x, int y) {

    int angle = 0, size = 50;
    for (int i = 0; i < 40; i++, angle = (angle + 10) % 360) {
        circle[i].x = x - COS[angle] * size;
        circle[i].y = y - SIN[angle] * size;
        //printf("%d - %d / %lf - %lf\n",circle[i].x, circle[i].y,COS[angle],SIN[angle]);
    }
}

void drawBall(SDL_Renderer *renderer, int x, int y) {
    SDL_Point circle[40];
    drawCircle(circle,x, y);
    SDL_SetRenderDrawColor(renderer,255, 0, 0, 255);
    SDL_RenderDrawLines(renderer, circle,40);
}