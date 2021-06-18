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
maillon_t * nouveau_maillon(float valeur, int i, int j, erreur_t * erreur) {
    maillon_t* maillon = calloc(1, sizeof(maillon_t));
    if (maillon == NULL){
        creer_erreur(erreur, CALLOC);
    } else{
        maillon->valeur = valeur;
        maillon->i = i;
        maillon->j = j;
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
            creer_erreur(erreur, INVALID_ARGUMENT);
            sprintf(erreur->message_erreur, "Aucun nouveau maillon n'a été ajouté\n");
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
        printf("[%f, %d, %d] -> ", maillon_courant ->valeur, maillon_courant->i, maillon_courant->j);
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

/* -------------------------------------------------------------------------------------------------------------------------- */
/* recherche_prec_selon_fonction: recherche_le_premier élément d'une liste vérifiant le prédicat d'adresse fonction_recherche */
/*                                                                                                                            */
/* En entrée: pointeur_debut_liste : adresse du pointeur de tête de la liste à afficher                                       */
/*            valeur : valeur avec laquelle le prédicat doit être vérifié                                                     */
/*            fonction_recherhe : pointeur sur un prédicat prenant en paramètre 2 flottants et retournant un booléen          */
/*                                                                                                                            */
/* En sortie: adresse de l'élément suivant du maillon précédent celui qui vérifie le prédicat                                 */
/* -------------------------------------------------------------------------------------------------------------------------- */
maillon_t** recherche_prec_selon_fonction(maillon_t** pointeur_debut_liste, float valeur, booleen_t (*fonction_recherche) (float, float)) {
    maillon_t ** maillon_prec = pointeur_debut_liste;
    maillon_t * maillon_courant = *pointeur_debut_liste;
    if(*pointeur_debut_liste != NULL) {
        while(maillon_courant != NULL && (*fonction_recherche)(valeur, maillon_courant->valeur) == FALSE) {
            maillon_courant = maillon_courant->suivant;
            maillon_prec = &((*maillon_prec)->suivant);
        }
    }
    return maillon_prec;
}

/* -------------------------------------------------------------------------------------------------------------------------- */
/* sauvegarder_liste_fichier: sauvegarde une liste dans un fichier texte                                                      */
/*                                                                                                                            */
/* En entrée: liste : adresse du pointeur de tête de la liste à afficher                                                      */
/*            nom_fichier : nom du fichier dans lequel la liste sera sauvegardée                                              */
/*			  erreur: le code d'erreur, permettant de gérer les potentielles erreurs en dehors de la                          */
/*                    fonction. Par défaut et en cas de non problème, vaut SUCCESS                                            */
/*                                                                                                                            */
/* En sortie: rien                                                                                                            */
/* -------------------------------------------------------------------------------------------------------------------------- */
void sauvegarder_liste_fichier(maillon_t ** liste, const char * nom_fichier, erreur_t * erreur) {
    FILE * descripteur_fichier = fopen(nom_fichier, "w");
    int retour_fprintf, ligne = 0;
    if(descripteur_fichier == NULL){
        creer_erreur(erreur, FICHIER);
        sprintf(erreur->message_erreur, "Erreur d'ouverture du fichier '%s'\n", nom_fichier);
    } else{
        maillon_t * maillon_courant = (*liste);
        while(maillon_courant != NULL) {
            retour_fprintf = fprintf(descripteur_fichier, "[%f %d %d] ->\n", maillon_courant->valeur, maillon_courant->i, maillon_courant->j);
            if(retour_fprintf == EOF){
                creer_erreur(erreur, FPRINTF);
                sprintf(erreur->message_erreur, "Erreur d'écriture ligne %d\n", ligne);
            }
            maillon_courant = maillon_courant->suivant;
            ligne++;
        }
        retour_fprintf = fprintf(descripteur_fichier, "NIL\n");
        if(retour_fprintf == EOF){
            creer_erreur(erreur, FPRINTF);
            sprintf(erreur->message_erreur, "Erreur d'écriture ligne %d\n", ligne);
        } else{
            printf("Liste enregistrée dans '%s'\n", nom_fichier);
        }
        fclose(descripteur_fichier);
    }
}