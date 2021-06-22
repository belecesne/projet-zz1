#include "../headers/labyrinthe.h"

labyrinthe_t *creerLabyrintheQqc(int lignes, int colonnes, double proba) {
    graph_t *graphe;
    graphe = genererGrapheGrille(lignes, colonnes);
    labyrinthe_t *labyrinthe;
    labyrinthe = malloc(sizeof(labyrinthe_t));
    labyrinthe->colonnes = colonnes;
    labyrinthe->lignes = lignes;
    labyrinthe->graphe = nouveauGraphe(lignes * colonnes);
    kruskalFisherYatesProba(graphe, labyrinthe, proba);
    return labyrinthe;
}

void kruskalFisherYatesProba(graph_t *graphe, labyrinthe_t *labyrinthe, double proba) {
    int lignes = labyrinthe->lignes, colonnes = labyrinthe->colonnes, err, i = 0;
    double alpha;
    fisherYates(graphe, lignes, colonnes);

    partition_t *partArbre = createPartition(lignes * colonnes, &err);
    initPartition(partArbre);
    while (i < graphe->listeAretes->tailleCourante) {
        alpha = rand() % 891975; // ;)
        alpha /= 891975.0;
        if (fusionPartition(partArbre, graphe->listeAretes->array[i]->n1.valeur,
                            graphe->listeAretes->array[i]->n2.valeur) == 0) {
            insererQueueVecteurArete(labyrinthe->graphe->listeAretes, graphe->listeAretes->array[i]);
        } else if (alpha <= proba) {
            insererQueueVecteurArete(labyrinthe->graphe->listeAretes, graphe->listeAretes->array[i]);
        } else {
            supprimerVecteurArete(&graphe->listeAretes, i);
            i--;
        }
        i++;
    }
    freePartition(partArbre);
    libererGraphe(graphe);
}


void fisherYates(graph_t *graphe, int lignes, int colonnes) {
    arete_t *temp;
    int i, j, m = graphe->listeAretes->tailleCourante;
    for (i = m - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = graphe->listeAretes->array[j];
        graphe->listeAretes->array[j] = graphe->listeAretes->array[i];
        graphe->listeAretes->array[i] = temp;
    }
}

void libererLabyrinthe(labyrinthe_t *lab) {
    int i;
    for (i = 0; i < lab->graphe->listeAretes->tailleCourante; i++) {
        free(lab->graphe->listeAretes->array[i]);
    }
    libererGraphe(lab->graphe);
    free(lab);
}