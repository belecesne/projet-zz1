#include "../headers/noeud.h"

void orientiation(noeud_t * n1, noeud_t * n2, int colonnes){
    int i,j,x,y;
    i = n1->valeur/colonnes;
    j = n1->valeur%colonnes;
    x = n2->valeur/colonnes;
    y = n2->valeur%colonnes;

    if (i == x) {
        n1->wall+=2;
        n2->wall+=1;
    }
    if(j == y){
        n1->wall+=4;
        n2->wall+=8;
    }
}
