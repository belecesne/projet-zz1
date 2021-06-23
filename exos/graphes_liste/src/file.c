/* -------------------------------------------------------------------- */
/*                               file .c                                */
/*                                                                      */
/* Role: fichier contenant les fonctions pour gérer une file            */
/* -------------------------------------------------------------------- */

#include "../headers/file.h"

/* --------------------------------------------------------------------------------------------------- */
/* affiche_elem_file_t : affiche un élément d'une file en console                                      */
/*                                                                                                     */
/* En entrée: element : élément à afficher                                                             */
/*            avant : texte à afficher avant l'élément                                                 */
/*            apres : texte à afficher après l'élément                                                 */
/*                                                                                                     */
/* En sortie: rien             										                                   */
/* --------------------------------------------------------------------------------------------------- */
void affiche_elem_file_t(elem_file_t element, char * avant, char * apres){
    printf("%s%d%s", avant, element, apres);
}

/* --------------------------------------------------------------------------------------------------- */
/* creer_file : crée une file vide                                                                     */
/*                                                                                                     */
/* En entrée: rien                                                                                     */
/*                                                                                                     */
/* En sortie: retourne un pointeur vers la file crée           										   */
/* --------------------------------------------------------------------------------------------------- */
file_t* creer_file() {
    file_t * file = calloc(1, sizeof(file_t));
    file->tab = malloc(TAILLE_BASE*sizeof(elem_file_t));
    file->taille = TAILLE_BASE;
    return file;
}

/* --------------------------------------------------------------------------------------------------- */
/* liberer_file : libère une file de la mémoire                                                        */
/*                                                                                                     */
/* En entrée: file : pointeur vers la structure file                                                   */
/*                                                                                                     */
/* En sortie: rien                                          										   */
/* --------------------------------------------------------------------------------------------------- */
void liberer_file(file_t * file){
    free(file->tab);
    free(file);
}

/* --------------------------------------------------------------------------------------------------- */
/* vider_file : défile l'intégralité des valeurs d'une file                                            */
/*                                                                                                     */
/* En entrée: file : pointeur vers la structure file                                                   */
/*                                                                                                     */
/* En sortie: rien                                             										   */
/* --------------------------------------------------------------------------------------------------- */
void vider_file(file_t * file){
    while(!file_est_vide(file)){
        defiler(file);
    }
}

/* --------------------------------------------------------------------------------------------------- */
/* file_est_vide : teste si la file est vide                                                           */
/*                                                                                                     */
/* En entrée: file : pointeur vers la structure file                                                   */
/*                                                                                                     */
/* En sortie: retourne vrai si la file est vide, faux sinon    										   */
/* --------------------------------------------------------------------------------------------------- */
int file_est_vide(file_t * file){
    return (file->tete == file->queue);
}

/* --------------------------------------------------------------------------------------------------- */
/* file_est_pleine : teste si le tableau dans lequel est contenu la file est plein                     */
/*                                                                                                     */
/* En entrée: file : pointeur vers la structure file                                                   */
/*                                                                                                     */
/* En sortie: retourne vrai si ce tableau est plein, faux sinon 									   */
/* --------------------------------------------------------------------------------------------------- */
int file_est_pleine(file_t * file) {
    return ((file->queue + 1) % file->taille == file->tete);
}

/* --------------------------------------------------------------------------------------------------- */
/* realloc_file : réalloue le tableau contenant la file                                                */
/*                                                                                                     */
/* En entrée: file : pointeur vers la structure file                                                   */
/*            coefficient de modification : scalaire par lequel la taille du tableau sera multipliée   */
/*                                                                                                     */
/* En sortie: rien                                            										   */
/* --------------------------------------------------------------------------------------------------- */
void reallouer_file(file_t * file, float coefficient_de_modification) {
    int nouvelle_taille, nb_element_apres_tete;
    elem_file_t * nouveau_tab;
    if(!file_est_vide(file)){
        nouvelle_taille = file->taille * coefficient_de_modification;
        if(nouvelle_taille < TAILLE_BASE){
            nouvelle_taille = TAILLE_BASE;
        }
        nouveau_tab = malloc(nouvelle_taille * sizeof(elem_file_t));
        if(file->queue > file->tete){
            memcpy(nouveau_tab, (file->tab + file->tete), file->nb_elements * sizeof(elem_file_t));
        } else{
            if(file->queue == 0){
                memcpy(nouveau_tab, (file->tab + file->tete), file->nb_elements * sizeof(elem_file_t));
            } else{
                nb_element_apres_tete = file->nb_elements - file->queue;
                memcpy(nouveau_tab, file->tab + file->tete, nb_element_apres_tete * sizeof(elem_file_t));
                memcpy(nouveau_tab + nb_element_apres_tete, file->tab, (file->nb_elements - nb_element_apres_tete) * sizeof(elem_file_t));
            }
        }
        free(file->tab);
        file->tab = nouveau_tab;
        file->taille = nouvelle_taille;
        file->tete = 0;
        file->queue = file->nb_elements;
    }
}

/* --------------------------------------------------------------------------------------------------- */
/* enfiler : insère une valeur dans la file                                                            */
/*                                                                                                     */
/* En entrée: file : pointeur vers la structure file                                                   */
/*            v : valeur à insérer dans la file                                                        */
/*                                                                                                     */
/* En sortie: rien                                          										   */
/* --------------------------------------------------------------------------------------------------- */
void enfiler(file_t * file, elem_file_t v) {
    if(file_est_pleine(file)){
        reallouer_file(file, 2);
    }
    file->tab[file->queue] = v;
    file->queue = (file->queue + 1) % file->taille;
    file->nb_elements ++;
}

/* --------------------------------------------------------------------------------------------------- */
/* sommet_file : retourne le sommet de la file                                                         */
/*                                                                                                     */
/* En entrée: file : pointeur vers la structure file                                                   */
/*                                                                                                     */
/* En sortie: retourne le sommet de la file                 										   */
/* --------------------------------------------------------------------------------------------------- */
elem_file_t tete_file(file_t * file){
    if(file_est_vide(file)){
        return (elem_file_t)NAN;
    } else{
        return *(file->tab + file->tete);
    }
}

/* --------------------------------------------------------------------------------------------------- */
/* defiler : retire une valeur de la file                                                              */
/*                                                                                                     */
/* En entrée: file : pointeur vers la structure file                                                   */
/*                                                                                                     */
/* En sortie: rien             										                                   */
/* --------------------------------------------------------------------------------------------------- */
void defiler(file_t * file) {
    if(!file_est_vide(file)) {
        file->tete = (file->tete + 1) % file->taille;
        file->nb_elements --;
        if(file->nb_elements <= 0.25 * file->taille){
            reallouer_file(file, 0.5);
        }
    }
}

/* --------------------------------------------------------------------------------------------------- */
/* afficher_file : défile toutes les valeurs, les affichent et les réenfilent                          */
/*                                                                                                     */
/* En entrée: file : pointeur vers la structure file                                                   */
/*                                                                                                     */
/* En sortie: rien             										                                   */
/* --------------------------------------------------------------------------------------------------- */
void afficher_file(file_t * file){
    elem_file_t valeur;
    file_t * file_temp = creer_file();
    printf("File = \n<--");
	while(!file_est_vide(file)) {
        valeur = tete_file(file);
		affiche_elem_file_t(valeur, " ", " --");
		defiler(file);
        enfiler(file_temp, valeur);
	}
    printf("\n");
    while(!file_est_vide(file_temp)){
        valeur = tete_file(file_temp);
		defiler(file_temp);
        enfiler(file, valeur);
    }
    liberer_file(file_temp);
}
