#include "../headers/maillon_level.h"

maillon_level_t* nouveau_maillon_level(liste_t * liste){
	maillon_level_t* maillon = calloc(1, sizeof(maillon_level_t));
	if(maillon == NULL){
		printf("Malloc raté\n");
	} else{
		maillon->class = liste;
		maillon->level = 1;
		maillon->suivant = NULL;
		maillon->prec = NULL;
	}
	return maillon;
}

void adjonction_level(maillon_level_t* cellule_precedente, maillon_level_t ** suivant_cell_prec, maillon_level_t* nouveau_maillon){
	if(suivant_cell_prec != NULL){
		if(nouveau_maillon == NULL){
			printf("Aucun nouveau maillon n'a été ajouté\n");
		} else{
			nouveau_maillon->suivant = (*suivant_cell_prec);
			nouveau_maillon->prec = cellule_precedente;
			(*suivant_cell_prec) = nouveau_maillon;
			if(nouveau_maillon->suivant != NULL){
				nouveau_maillon->suivant->prec = nouveau_maillon;
			}
		}
	}
}

void suppression_level(maillon_level_t* maillon_suppr, maillon_level_t * maillon_suiv){
	if(maillon_suppr != NULL){
		if(maillon_suppr->prec != NULL) maillon_suppr->prec->suivant = maillon_suppr->suivant;
		if(maillon_suppr->suivant != NULL) maillon_suppr->suivant->prec = maillon_suppr->prec;
		maillon_suppr->prec = NULL;
		maillon_suppr->class = NULL;
		maillon_suppr->level = -1;
		maillon_suppr->suivant = maillon_suiv;
	}
}

void liberer_liste_level(maillon_level_t * debut) {
	maillon_level_t *maillon_courant = debut;
	maillon_level_t *sauvegarde_adresse_maillon;
	while (maillon_courant != NULL) {
		sauvegarde_adresse_maillon = maillon_courant;
		liberer_liste(maillon_courant->class);
		maillon_courant = sauvegarde_adresse_maillon->suivant;
		free(sauvegarde_adresse_maillon);
	}
}