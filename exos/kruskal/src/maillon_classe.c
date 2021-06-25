#include "../headers/maillon_classe.h"


void insertionTeteClasse(maillon_classe_t **tete, maillon_classe_t *maillon) {
    if (tete != NULL) {
        maillon->suivant = *tete;
        *tete = maillon;
    }
}

maillon_classe_t *creerMaillon(liste_t *classe) {
    maillon_classe_t *maillon;
    maillon = malloc(sizeof(maillon_classe_t));
    if (maillon != NULL) {
        maillon->suivant = NULL;
        maillon->classe = classe;
    }
    return maillon;
}

maillon_classe_t *tableauVersListe(liste_t **classes, int taille) {
    maillon_classe_t *liste;
    int i;
    liste = NULL;
    for (i = 0; i < taille; i++) {
        if (classes[i]->tete != NULL) {
            insertionTeteClasse(&liste, creerMaillon(classes[i]));
        }
    }
    return liste;
}

void libererListeClasses(maillon_classe_t *tete) {
    maillon_classe_t *courant, *temp;
    courant = tete;
    while (courant) {
        temp = courant->suivant;
        free(courant);
        courant = temp;
    }
}