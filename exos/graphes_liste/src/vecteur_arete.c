#include "../headers/vecteur_arete.h"


vecteur_arete_t * creerVecteurArete(int taille){
    vecteur_arete_t * liste = malloc(sizeof(vecteur_arete_t));
    if(liste){
        liste->array = malloc(taille*sizeof(vec_arete_type));
        liste->tailleCourante = 0;
        liste->taille = taille;
    }
    return liste;
}

void reallouerVecteurArete(vecteur_arete_t * liste){
    int nouvelleTaille = liste->tailleCourante * 2;
    vecteur_arete_t * nouveauTab = malloc(nouvelleTaille * sizeof(vec_arete_type));
    memcpy(nouveauTab, liste->array, (liste->tailleCourante) * sizeof(vec_arete_type));
    free(liste->array);
    liste->array = nouveauTab;
    liste->taille *= 2;
}

void insererQueueVecteurArete(vecteur_arete_t * liste, vec_arete_type inser){
        if(liste->tailleCourante == liste->taille){
            reallouerVecteurArete(liste);
        }
        liste->array[liste->tailleCourante] = inser;
        liste->tailleCourante++;
}

void supprimerVecteurArete(vecteur_arete_t ** liste, int index){
    free((*liste)->array[index]);
    (*liste)->array[index] =(*liste)->array[(*liste)->tailleCourante-1];
    (*liste)->tailleCourante--;
}

void libererVecteurArete(vecteur_arete_t * liste){
    free(liste->array);
    free(liste);
}