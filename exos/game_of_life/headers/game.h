#ifndef GAME
#define GAME

#define GAME_LENGTH 30

void initRules();
void applyRule(int game[][GAME_LENGTH], int copy[][GAME_LENGTH], int gameLength, int * rule, int pointx, int pointy);
void copyMatrix(int copy[][GAME_LENGTH], int matrix[][GAME_LENGTH], int length);

#endif