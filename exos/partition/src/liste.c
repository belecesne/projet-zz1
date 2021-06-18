#include "../headers/liste.h"


liste_t *nouvelle_liste() {
    liste_t *liste;
    liste = malloc(sizeof(liste_t));
    if (liste) {
        liste->tete = NULL;
        liste->queue = NULL;
    }
    return liste;
}

void insertionTete(liste_t *liste, maillon_t *maillon) {
    maillon->suivant = liste->tete;
    liste->tete = maillon;
    if (liste->queue == NULL) {
        liste->queue = maillon;
    }
}

void afficher_liste(liste_t * liste) {
    maillon_t * maillon_courant = liste->tete;
    while (maillon_courant != NULL) {
        printf("%d,", maillon_courant->valeur);
        maillon_courant = maillon_courant->suivant;
    }
}

void liberer_liste(liste_t  * liste) {
    maillon_t *maillon_courant = liste->tete;
    maillon_t *sauvegarde_adresse_maillon;
    while (maillon_courant != NULL) {
        sauvegarde_adresse_maillon = maillon_courant;
        maillon_courant = sauvegarde_adresse_maillon->suivant;
        free(sauvegarde_adresse_maillon);
    }
    liste->tete = NULL;
    liste->queue = NULL;
    free(liste);
    liste = NULL;

}

void fusion_liste(liste_t *petite, liste_t *grande){
    petite->queue->suivant = grande->tete;
    grande->tete = petite->tete;
    petite->tete = NULL;
}

