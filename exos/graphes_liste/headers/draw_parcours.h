#ifndef DRAW_PARCOURS
#define DRAW_PARCOURS

#include "cellule.h"
#include "file.h"

int drawParcours(SDL_Renderer * , file_t *, cellule_t *, cellule_t **, int );

void reinitEtat(cellule_t **, int );
#endif //DRAW_PARCOURS
