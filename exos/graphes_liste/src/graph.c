#include "../headers/graph.h"


graph_t *nouveau_graphe(int nbNoeuds) {
    graph_t * graph;
    graph = malloc(sizeof(graph_t));
    if (graph) {
        graph->tabListes = calloc(nbNoeuds, sizeof(maillon_graphe_t *));
        graph->nbNoeuds = nbNoeuds;
    }
    return graph;
}

void insertionArrete(graph_t * graphe, int x, int y) {
    int max = x > y ? x : y;
    int min = x < y ? x : y;
    maillon_graphe_t * maillon = nouveau_maillon_graphe(max);
    if((maillon != NULL)) {
        maillon->suivant = graphe->tabListes[min];
        graphe->tabListes[min] = maillon;
    }
}

void liberer_graphe(graph_t * graphe) {
    for(int i = 0; i < graphe->nbNoeuds; i++ ){
        maillon_graphe_t *maillon_courant = graphe->tabListes[i];
        maillon_graphe_t *sauvegarde_adresse_maillon;
        while (maillon_courant != NULL) {
            sauvegarde_adresse_maillon = maillon_courant;
            maillon_courant = sauvegarde_adresse_maillon->suivant;
            free(sauvegarde_adresse_maillon);
        }
    }
    free(graphe->tabListes);
    free(graphe);
    graphe = NULL;
}

void generateGraphvizGraph(graph_t * graphe, char * filename) {
    char buffer[BUFSIZ];
    sprintf(buffer, "%s.dot", filename);
    FILE * dotFile = fopen(buffer, "w");
    fputs("graph G {\n", dotFile);
    for(int i = 0; i < graphe->nbNoeuds; i++) { 
        fprintf(dotFile, "  \"%d\";\n", i);
        maillon_graphe_t * cour = graphe->tabListes[i];
        while(cour != NULL) {
            fprintf(dotFile, "  \"%d\" -- \"%d\";\n", i, cour->noeud);
            cour = cour->suivant;
        }
    }
    fputs("}\n", dotFile);
    fclose(dotFile);
    sprintf(buffer, "dot -Tsvg %s.dot > %s.svg", filename, filename);
    system(buffer);
}

union_find_t * getUnionFindFromGraph(graph_t * graphe) {
    int err;
    union_find_t * part = createUnionFind(graphe->nbNoeuds, &err);
    initUnionFind(part);
    for(int i = 0; i < graphe->nbNoeuds; i++) {
        maillon_graphe_t * cour = graphe->tabListes[i];
        while(cour != NULL) {
            fusionUnionFind(part, i, cour->noeud);
            cour = cour->suivant;
        }
    }
    return part;
}

void generateConnectedComponents(graph_t * graphe, char * filename) {
    union_find_t * part = getUnionFindFromGraph(graphe);
    for(int i = 0; i < part->size; i++) {
        if(part->level[i] != -1) {
            char buffer[BUFSIZ];
            sprintf(buffer, "%s_%d.dot", filename, i);
            FILE * dotFile = fopen(buffer, "w");
            fputs("graph G {\n", dotFile);
            printf("%p\n", part->classes[i]->tete);
            maillon_t * cour = part->classes[i]->tete;
            while(cour != NULL) {
                int currNode = cour->valeur;
                fprintf(dotFile, "  \"%d\";\n", currNode);
                maillon_graphe_t * courG = graphe->tabListes[currNode];
                while(courG != NULL) {
                    fprintf(dotFile, "  \"%d\" -- \"%d\";\n", currNode, courG->noeud);
                    courG = courG->suivant;
                }
                cour = cour -> suivant;
            }
            fputs("}\n", dotFile);
            fclose(dotFile);
            sprintf(buffer, "dot -Tsvg %s_%d.dot > %s_%d.svg", filename, i, filename, i);
            system(buffer);
        }
    }
}