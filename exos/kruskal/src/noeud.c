#include "../headers/noeud.h"

noeud_t * creerNoeud(int valeur){
    noeud_t * noeud;
    noeud  = malloc(sizeof(noeud_t));
    if(noeud){
        noeud->valeur = valeur;
    }
    return noeud;
}