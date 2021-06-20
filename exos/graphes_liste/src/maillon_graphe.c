/* -------------------------------------------------------------------- */
/*                              liste.c                                 */
/*                                                                      */
/* Role: fichier contenant les fonctions pour gérer une liste           */
/* -------------------------------------------------------------------- */

#include "../headers/maillon_graphe.h"

/* --------------------------------------------------------------------------------------------------- */
/* nouveau_maillon: crée un nouveau maillon                                                            */
/*                                                                                                     */
/* En entrée: valeur: valeur a stocké                                                                  */
/*            i: indice de ligne                                                                       */
/*            j: indice de colone                                                                      */
/*                                                                                                     */
/* En sortie: retourne le nouveau maillon                   										   */
/* --------------------------------------------------------------------------------------------------- */
maillon_graphe_t * nouveau_maillon_graphe(int noeud) {
    maillon_graphe_t * maillon = calloc(1, sizeof(maillon_graphe_t));
    if (maillon == NULL){
        printf("Malloc raté\n");
    } else{
        maillon->noeud = noeud;
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
void adjonction_graphe(maillon_graphe_t ** cellule_precedente, maillon_graphe_t * nouveau_maillon) {
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
void suppression_graphe(maillon_graphe_t ** cellule_precedente) {
    if(cellule_precedente != NULL && (*cellule_precedente) != NULL) {
        maillon_graphe_t* adresse_cellule_a_supprimer = (*cellule_precedente);
        (*cellule_precedente) = adresse_cellule_a_supprimer -> suivant;
        free(adresse_cellule_a_supprimer);
    }
}