#include "../headers/graph.h"


graph_t *nouveauGraphe(int nbNoeuds) {
    graph_t *graph;
    graph = malloc(sizeof(graph_t));
    if (graph) {
        graph->nbNoeuds = nbNoeuds;
        graph->listeAretes = creerVecteurArete(DEFAULT_VECTOR_SIZE);
    }
    return graph;
}

void insertionArrete(graph_t *graphe, arete_t *arete) {
    insererQueueVecteurArete(graphe->listeAretes, arete);
}

void libererGraphe(graph_t *graphe) {
    libererVecteurArete(graphe->listeAretes);
    free(graphe);
}

void generateGraphvizGraph(graph_t *graphe, char *filename) {
    char buffer[BUFSIZ];
    sprintf(buffer, "%s.dot", filename);
    FILE *dotFile = fopen(buffer, "w");
    fputs("graph G {\n", dotFile);
    int i;
    for (i = 0; i < graphe->nbNoeuds; i++) {
        fprintf(dotFile, "  \"%d\";\n", i);
    }
    for (i = 0; i < graphe->listeAretes->tailleCourante; i++) {
        fprintf(dotFile, "  \"%d\" -- \"%d\";\n", graphe->listeAretes->array[i]->n1.valeur,
                graphe->listeAretes->array[i]->n2.valeur);
    }

    fputs("}\n", dotFile);
    fclose(dotFile);
    sprintf(buffer,
            "dot -Tsvg %s.dot > %s.svg", filename, filename);
    system(buffer);
}

void generateGraphvizGraphGrid(graph_t *graphe, char *filename, int colonnes) {
    char buffer[BUFSIZ];
    int posX, posY,i;
    sprintf(buffer, "%s.dot", filename);
    FILE *dotFile = fopen(buffer, "w");
    fputs("graph G {\n", dotFile);
    for (i = 0; i < graphe->nbNoeuds; i++) {
        posX = i / colonnes;
        posY = i % colonnes;
        printf("posx= %d, posy = %d\n", posX, posY);
        fprintf(dotFile, "  \"%d\" [pos=\"%d,%d\"];\n", i, posY + 1, posX + 1);
    }
    for (i = 0; i < graphe->listeAretes->tailleCourante; i++) {
        fprintf(dotFile, "  \"%d\" -- \"%d\";\n", graphe->listeAretes->array[i]->n1.valeur, graphe->listeAretes->array[i]->n2.valeur);
    }

    fputs("}\n", dotFile);
    fclose(dotFile);
    sprintf(buffer,
            "dot -Tsvg %s.dot > %s.svg", filename, filename);
    system(buffer);
}

partition_t *getParitionFromGraph(graph_t *graphe) {
    int err;
    int i;
    partition_t *part = createPartition(graphe->nbNoeuds, &err);
    initPartition(part);
    for (i = 0; i < graphe->listeAretes->tailleCourante; i++) {
        fusionPartition(part, graphe->listeAretes->array[i]->n1.valeur, graphe->listeAretes->array[i]->n2.valeur);
    }
    return part;
}

void generateConnectedComponents(graph_t *graphe, char *filename) {
    partition_t *part = getParitionFromGraph(graphe);
    maillon_classe_t *classes;
    maillon_classe_t *classeCourante, *tempClasse;
    maillon_t *elementCourant;
    int currNode,i;
    char buffer[BUFSIZ];
    classes = getAllClasses(part);
    classeCourante = classes;
    while (classeCourante != NULL) {
        sprintf(buffer, "%s_%d.dot", filename, classeCourante->classe->racine);
        FILE *dotFile = fopen(buffer, "w");
        fputs("graph G {\n", dotFile);
        elementCourant = classeCourante->classe->tete;
        while (elementCourant != NULL) {
            currNode = elementCourant->valeur;
            fprintf(dotFile, "  \"%d\";\n", currNode);
            for (i = 0; i < graphe->listeAretes->tailleCourante; i++) {
                if (currNode == graphe->listeAretes->array[i]->n1.valeur) {
                    fprintf(dotFile, "  \"%d\" -- \"%d\";\n", currNode, graphe->listeAretes->array[i]->n2.valeur);
                }
            }
            elementCourant = elementCourant->suivant;
        }
        fputs("}\n", dotFile);
        fclose(dotFile);
        sprintf(buffer,
                "dot -Tsvg %s_%d.dot > %s_%d.svg", filename, classeCourante->classe->racine, filename,
                classeCourante->classe->racine);
        system(buffer);
        tempClasse = classeCourante;
        classeCourante = classeCourante->suivant;
        free(tempClasse);
    }
    freePartition(part);
}

graph_t *genererGrapheGrille(int lignes, int colonnes) {
    int i, j, nbNoeud = lignes * colonnes;
    noeud_t noeud, nord, sud, est, ouest;
    graph_t *graphe;
    graphe = nouveauGraphe(lignes * colonnes);
    for (i = 0; i < lignes; i++) {
        for (j = (i % 2 == 0 ? 0 : 1); j < colonnes; j += 2) {
            noeud.valeur = i * colonnes + j;
            nord.valeur = (i - 1) * colonnes + j;
            sud.valeur = (i + 1) * colonnes + j;
            ouest.valeur = i * colonnes + j - 1;
            est.valeur = i * colonnes + j + 1;
            if (nord.valeur >= 0) {
                insererQueueVecteurArete(graphe->listeAretes, creerArete(nord, noeud, 1));
            }
            if (sud.valeur < nbNoeud) {
                insererQueueVecteurArete(graphe->listeAretes, creerArete(sud, noeud, 1));
            }
            if (ouest.valeur / colonnes == i && ouest.valeur >= 0) {
                insererQueueVecteurArete(graphe->listeAretes, creerArete(ouest, noeud, 1));
            }
            if (est.valeur / colonnes == i && est.valeur < nbNoeud) {
                insererQueueVecteurArete(graphe->listeAretes, creerArete(est, noeud, 1));
            }
        }
    }
    return graphe;
}
/*
graph_t* kruskal(graph_t* graphe){
	tas_t* tas = creerTas(graphe->nbNoeuds);
	maillon_arete_t* courant = graphe->listeAretes;
	arete_t* areteMin, * nouvelleArete;
	while(courant != NULL){
		ajoutTas(tas, courant->arete);
		courant = courant->suivant;
	}
	int err;
	partition_t* partArbre = createPartition(graphe->nbNoeuds, &err);
	initPartition(partArbre);
	graph_t* arbre = nouveauGraphe(graphe->nbNoeuds);
	while(!tasVide(tas)){
		areteMin = suppressionRacine(tas, 0);
		if(fusionPartition(partArbre, areteMin->n1.valeur, areteMin->n2.valeur) == 0){
			nouvelleArete = creerArete(areteMin->n1, areteMin->n2, areteMin->poids);
			insertionTeteArete(&arbre->listeAretes, creerMaillonArete(nouvelleArete));
		}
	}
	libererTas(tas);
	freePartition(partArbre);
	return arbre;
}*/