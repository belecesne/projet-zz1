#include "../headers/maillon_arete.h"

void insertionTeteArete(maillon_arete_t **tete, maillon_arete_t *maillon) {
    if (tete != NULL) {
        maillon->suivant = *tete;
        *tete = maillon;
    }
}

maillon_arete_t * creerMaillonArete(arete_t * arete) {
    maillon_arete_t *maillon;
    maillon = malloc(sizeof(maillon_arete_t));
    if (maillon != NULL) {
        maillon->suivant = NULL;
        maillon->arete = arete;
    }
    return maillon;
}


void libererListeArretes(maillon_arete_t * tete) {
    maillon_arete_t *courant, *temp;
    courant = tete;
    while (courant) {
        temp = courant->suivant;
        free(courant->arete);
        free(courant);
        courant = temp;
    }
}