#include "../headers/arete.h"

arete_t *creerArete(noeud_t n1, noeud_t n2, int poids) {
    arete_t *arete;
    arete = malloc(sizeof(arete_t));
    if (arete) {
        if (n1.valeur < n2.valeur) {
            arete->n1 = n1;
            arete->n2 = n2;
        } else {
            arete->n1 = n2;
            arete->n2 = n1;
        }
        arete->poids = poids;
    }
    return arete;
}