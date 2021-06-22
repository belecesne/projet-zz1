#include "../headers/vecteur.h"


vecteur_t * creerVecteur(int taille){
    vecteur_t * liste = malloc(sizeof(vecteur_t));
    if(liste){
        liste->array = malloc(taille*sizeof(vec_type));
        liste->tailleCourante = 0;
        liste->taille = taille;
    }
    return liste;
}

vecteur_t * reallouerVecteur(vecteur_t * liste){
    int nouvelleTaille = liste->tailleCourante * 2;
    vec_type * nouveauTab = malloc(nouvelleTaille * sizeof(vec_type));
    memcpy(nouveauTab, liste->array, (liste->tailleCourante) * sizeof(vec_type));
    free(liste->array);
    liste->array = nouveau_tab;
    liste->taille *= 2;
}

void insererQueueVecteur(vecteur_t * liste, vec_type inser){
        liste->array[liste->tailleCourante] = inser;
        liste->tailleCourante++;
}

void supprimerVecteur(vecteur_t * liste, int index){
    liste->array[index] = liste->array[liste->tailleCourante];
    liste->tailleCourante--;
}