#include "../headers/game.h"

int modulo(int a, int b) {
    while(a < 0) {
        a = a + b;
    }
    return a%b;
}

void copyMatrix(int copy[][GAME_LENGTH], int matrix[][GAME_LENGTH], int length) {
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < GAME_LENGTH; j++) {
            matrix[i][j] = copy[i][j];
        }
    }
}

void applyRule(int game[][GAME_LENGTH], int copy[][GAME_LENGTH], int gameLength, int * rule, int pointx, int pointy) {
    int valueToApply = rule[0];
    int count = 1;
    for(int i = pointx-1; i <= pointx+1; i++) {
        for(int j = pointy-1; j <= pointy+1; j++) {
            if((i != pointx) || (j != pointy)) {
                count += game[modulo(i, gameLength)][modulo(j, gameLength)];
            }
        }
    }
    copy[pointx][pointy] = (game[pointx][pointy] == !valueToApply) ? rule[count] : game[pointx][pointy];
}