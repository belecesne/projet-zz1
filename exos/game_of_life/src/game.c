#include "../headers/game.h"
#include <stdio.h>

int modulo(int a, int b) {
    while(a < 0) {
        a = a + b;
    }
    return a%b;
}

void applyRule(int game[][30], int gameLength, int rule[][3], int pointx, int pointy) {
    int boo = 1;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if((i != 0) || (j != 0)) {
                if(game[modulo(i+pointx,gameLength)][modulo(j+pointy,gameLength)] != rule[i+1][j+1]) {
                    boo = 0;
                }
            }
        }
    }
    game[pointx][pointy] = boo ? rule[1][1] : game[pointx][pointy];
}