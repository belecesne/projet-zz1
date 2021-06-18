/* -------------------------------------------------------------------- */
/*                              liste.c                                 */
/*                                                                      */
/* Role: fichier contenant les fonctions pour gérer une liste           */
/* -------------------------------------------------------------------- */

#include "liste.h"

/* --------------------------------------------------------------------------------------------------- */
/* nouvelle_liste: crée une nouvelle liste                                                             */
/*                                                                                                     */
/* En entrée: rien                                                                                     */
/*                                                                                                     */
/* En sortie: retourne NULL, car la liste est vide          										   */
/* --------------------------------------------------------------------------------------------------- */
maillon_t * nouvelle_liste() {
    return NULL;
}

/* --------------------------------------------------------------------------------------------------- */
/* nouveau_maillon: crée un nouveau maillon                                                            */
/*                                                                                                     */
/* En entrée: valeur: valeur a stocké                                                                  */
/*            i: indice de ligne                                                                       */
/*            j: indice de colone                                                                      */
/*                                                                                                     */
/* En sortie: retourne le nouveau maillon                   										   */
/* --------------------------------------------------------------------------------------------------- */
maillon_t * nouveau_maillon(int valeur, erreur_t * erreur) {
    maillon_t* maillon = calloc(1, sizeof(maillon_t));
    if (maillon == NULL){
        printf("Malloc raté\n");
    } else{
        maillon->valeur = valeur;
    }
    return maillon;
}

/* ------------------------------------------------------------------------------------------------------------- */
/* adjonction: insère un maillon derrière un autre                                                               */
/*                                                                                                               */
/* En entrée: cellule_precedente: pointeur vers l'élément suivant du maillon après lequel l'insertion sera faite */
/*            nouveau_maillon: maillon à insérer                                                                 */
/*			  erreur: le code d'erreur, permettant de gérer les potentielles erreurs en dehors de la             */
/*                    fonction. Par défaut et en cas de non problème, vaut SUCCESS                               */
/*                                                                                                               */
/* En sortie: rien                                             										             */
/* ------------------------------------------------------------------------------------------------------------- */
void adjonction(maillon_t ** cellule_precedente, maillon_t * nouveau_maillon, erreur_t * erreur) {
    if(cellule_precedente != NULL) {
        if (nouveau_maillon == NULL){
            printf("Aucun nouveau maillon n'a été ajouté\n");
        } else{
            nouveau_maillon -> suivant = (*cellule_precedente);
            (*cellule_precedente) = nouveau_maillon;
        }
    }
}

/* ----------------------------------------------------------------------------------------------------- */
/* liberer_matrice: supprime un maillon derrière un autre                                                */
/*                                                                                                       */
/* En entrée: cellule_precedente: pointeur vers l'élément suivant du maillon précédent celui à supprimer */
/*                                                                                                       */
/* En sortie: rien													                                     */
/* ----------------------------------------------------------------------------------------------------- */
void suppression(maillon_t ** cellule_precedente) {
    if(cellule_precedente != NULL && (*cellule_precedente) != NULL) {
        maillon_t* adresse_cellule_a_supprimer = (*cellule_precedente);
        (*cellule_precedente) = adresse_cellule_a_supprimer -> suivant;
        free(adresse_cellule_a_supprimer);
    }
}

/* ------------------------------------------------------------------------------------ */
/* afficher_liste: affiche une liste                                                    */
/*                                                                                      */
/* En entrée: pointeur_debut_liste : adresse du pointeur de tête de la liste à afficher */
/*                                                                                      */
/* En sortie: rien													                    */
/* ------------------------------------------------------------------------------------ */
void afficher_liste(maillon_t ** pointeur_debut_liste) {
    maillon_t * maillon_courant = *pointeur_debut_liste;
    printf("Liste = \n");
    while(maillon_courant != NULL) {
        printf("[%d] -> ", maillon_courant ->valeur);
        maillon_courant = maillon_courant -> suivant;
    }
    printf("NULL\n\n");
}

/* ------------------------------------------------------------------------------------ */
/* liberer_liste: libère une liste de la mémoire                                        */
/*                                                                                      */
/* En entrée: pointeur_debut_liste : adresse du pointeur de tête de la liste à libérer  */
/*                                                                                      */
/* En sortie: rien													                    */
/* ------------------------------------------------------------------------------------ */
void liberer_liste(maillon_t ** pointeur_debut_liste) {
    maillon_t * maillon_courant = *pointeur_debut_liste;
    maillon_t * sauvegarde_adresse_maillon;
    while(maillon_courant != NULL) {
        sauvegarde_adresse_maillon = maillon_courant;
        maillon_courant = sauvegarde_adresse_maillon -> suivant;
        free(sauvegarde_adresse_maillon);
    }
}