#include "../headers/union_find.h"


union_find_t *createUnionFind(int size, int *erreur) {
    *erreur = 0;
    union_find_t *unionFind;
    unionFind = malloc(sizeof(union_find_t));
    if (unionFind == NULL) {
        *erreur = 1;
    } else {
        unionFind->partition = malloc(size * sizeof(int));
        if (unionFind->partition == NULL) {
            *erreur = 2;
        } else {
            unionFind->level = malloc(size * sizeof(int));
            if (unionFind->partition == NULL) {
                *erreur = 3;
            } else {
                unionFind->size = size;
                unionFind->classes = malloc(size * sizeof(liste_t *));
                if (unionFind->classes == NULL) {
                    *erreur = 4;
                }
            }
        }
    }
    return unionFind;
}


void freeUnionFind(union_find_t *unionFind) {
    if (unionFind) {
        if (unionFind->partition) {
            free(unionFind->partition);
            unionFind->partition = NULL;
        }
        if (unionFind->level) {
            free(unionFind->level);
            unionFind->level = NULL;
        }
        if (unionFind->classes) {
            for (int i = 0; i < unionFind->size; i++) {
                liberer_liste(unionFind->classes[i]);
            }
            free(unionFind->classes);
        }
        free(unionFind);
    }
}

void initUnionFind(union_find_t *unionFind) {
    for (int i = 0; i < unionFind->size; ++i) {
        unionFind->level[i] = 0;
        unionFind->partition[i] = i;
        unionFind->classes[i] = nouvelle_liste();
        insertionTete(unionFind->classes[i], nouveau_maillon(i));
    }
}

void printUnionFind(union_find_t *unionFind) {
    printf("-----------------------------------------------\n");
    printf("Hauteur :\n");
    for (int i = 0; i < unionFind->size; i++) {
        printf("%d - ", unionFind->level[i]);
    }
    printf("\nValeur :\n");
    for (int i = 0; i < unionFind->size; i++) {
        printf("%d - ", unionFind->partition[i]);
    }
    printf("\n\n");
    printf("-----------------------------------------------\n\n");

}


int rootNodeUnionFind(union_find_t *unionFind, int node) {
    while (node != unionFind->partition[node]) {
        node = unionFind->partition[node];
    }
    return node;
}

void fusionUnionFind(union_find_t *unionFind, int x, int y) {
    int xRoot, yRoot;
    if (x < unionFind->size && y < unionFind->size) {
        xRoot = rootNodeUnionFind(unionFind, x);
        yRoot = rootNodeUnionFind(unionFind, y);
        if (xRoot != yRoot) { // Ils ne sont pas dans la même classe
            if (unionFind->level[xRoot] < unionFind->level[yRoot]) { //
                unionFind->partition[xRoot] = yRoot;
                unionFind->level[xRoot] = -1;
                fusion_liste(unionFind->classes[xRoot], unionFind->classes[yRoot]);

            } else if (unionFind->level[xRoot] > unionFind->level[yRoot]) {
                unionFind->partition[yRoot] = xRoot;
                unionFind->level[yRoot] = -1;
                fusion_liste(unionFind->classes[yRoot], unionFind->classes[xRoot]);
            } else {
                unionFind->partition[yRoot] = xRoot;
                fusion_liste(unionFind->classes[yRoot], unionFind->classes[xRoot]);
                unionFind->level[yRoot] = -1;
                unionFind->level[xRoot]++;
            }
        }
    } else {
        printf("Impossible de fusionner les classes de %d et %d\n", x, y);
    }
}

void printClassUnionFind(union_find_t *unionFind, int node) {
    int root;
    root = rootNodeUnionFind(unionFind, node);
    printf("Classe de %d\n{",node);
    afficher_liste(unionFind->classes[root]);
    printf("\b}\n\n");
}

void printAllClassesUnionFind(union_find_t *unionFind) {
    int sommeElements = 0;
    int i = 0;
    while(sommeElements < unionFind->size) {
        if(unionFind->classes[i]->tete != NULL){
            sommeElements+= unionFind->classes[i]->nbElements;
            printf("Classe de %d :\n{", i);
            afficher_liste(unionFind->classes[i]);
            printf("\b}\n\n");
        }
        i++;
    }
}

void makeGraphvizGraph(union_find_t *union_find, char *fileName) {
    char fullFileName[BUFSIZ];
    strcpy(fullFileName, fileName);
    strcat(fullFileName, ".dot");
    FILE *dotFile = fopen(fullFileName, "w");
    fputs("digraph G {\n", dotFile);
    for (int i = 0; i < (union_find->size); i++) {
        fprintf(dotFile, "   \"%d\" -> \"%d\";\n", i, union_find->partition[i]);
    }
    fputs("}", dotFile);
    fclose(dotFile);
    strcpy(fullFileName, "dot -Tsvg ");
    strcat(fullFileName, fileName);
    strcat(fullFileName, ".dot > ");
    strcat(fullFileName, fileName);
    strcat(fullFileName, ".svg");
    system(fullFileName);
}