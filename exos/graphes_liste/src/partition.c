#include "../headers/partition.h"


partition_t *createPartition(int size, int *erreur) {
    *erreur = 0;
    partition_t *partition;
    partition = malloc(sizeof(partition_t));
    if (partition == NULL) {
        *erreur = 1;
    } else {
        partition->parent = malloc(size * sizeof(int));
        if (partition->parent == NULL) {
            *erreur = 2;
        } else {
            partition->level = malloc(size * sizeof(int));
            if (partition->parent == NULL) {
                *erreur = 3;
            } else {
                partition->size = size;
                partition->classes = malloc(size * sizeof(liste_t *));
                if (partition->classes == NULL) {
                    *erreur = 4;
                }
            }
        }
    }
    return partition;
}


void freePartition(partition_t *partition) {
    if (partition) {
        if (partition->parent) {
            free(partition->parent);
            partition->parent = NULL;
        }
        if (partition->level) {
            free(partition->level);
            partition->level = NULL;
        }
        if (partition->classes) {
            for (int i = 0; i < partition->size; i++) {
                liberer_liste(partition->classes[i]);
            }
            free(partition->classes);
        }
        free(partition);
    }
}

void initPartition(partition_t *partition) {
    for (int i = 0; i < partition->size; ++i) {
        partition->level[i] = 0;
        partition->parent[i] = i;
        partition->classes[i] = nouvelle_liste();
        insertionTete(partition->classes[i], nouveau_maillon(i));
    }
}

void printPartition(partition_t *partition) {
    printf("-----------------------------------------------\n");
    printf("Hauteur :\n");
    for (int i = 0; i < partition->size; i++) {
        printf("%d - ", partition->level[i]);
    }
    printf("\nValeur :\n");
    for (int i = 0; i < partition->size; i++) {
        printf("%d - ", partition->parent[i]);
    }
    printf("\n\n");
    printf("-----------------------------------------------\n\n");

}


int rootNodePartition(partition_t *partition, int node) {
    while (node != partition->parent[node]) {
        node = partition->parent[node];
    }
    return node;
}

void fusionPartition(partition_t *partition, int x, int y) {
    int xRoot, yRoot;
    if (x < partition->size && y < partition->size) {
        xRoot = rootNodePartition(partition, x);
        yRoot = rootNodePartition(partition, y);
        if (xRoot != yRoot) { // Ils ne sont pas dans la même classe
            if (partition->level[xRoot] < partition->level[yRoot]) { //
                partition->parent[xRoot] = yRoot;
                partition->level[xRoot] = -1;
                fusion_liste(partition->classes[xRoot], partition->classes[yRoot]);

            } else if (partition->level[xRoot] > partition->level[yRoot]) {
                partition->parent[yRoot] = xRoot;
                partition->level[yRoot] = -1;
                fusion_liste(partition->classes[yRoot], partition->classes[xRoot]);
            } else {
                partition->parent[yRoot] = xRoot;
                fusion_liste(partition->classes[yRoot], partition->classes[xRoot]);
                partition->level[yRoot] = -1;
                partition->level[xRoot]++;
            }
        }
    }
}

liste_t *getClassNode(partition_t *partition, int node) {
    int root;
    root = rootNodePartition(partition, node);
    return (partition->classes[root]);
}

maillon_classe_t *getAllClasses(partition_t *partition) {
    return tableauVersListe(partition->classes, partition->size);
}

void printClassPartition(partition_t *partition, int node) {
    printf("Classe de %d\n{", node);
    afficher_liste(getClassNode(partition,node), ",");
    printf("\b}\n\n");
}

void printAllClassesPartition(partition_t *partition) {
    maillon_classe_t * classes;
    maillon_classe_t * courant;
    classes = getAllClasses(partition);
    courant = classes;
    printf("[");
    while(courant){
        printf("{");
        afficher_liste(courant->classe,",");
        printf("\b},");
        courant = courant->suivant;
    }
    printf("\b]\n");
    libererListeClasses(classes);
}

void makeGraphvizGraph(partition_t *parent, char *fileName) {
    char fullFileName[BUFSIZ];
    strcpy(fullFileName, fileName);
    strcat(fullFileName, ".dot");
    FILE *dotFile = fopen(fullFileName, "w");
    fputs("digraph G {\n", dotFile);
    for (int i = 0; i < (parent->size); i++) {
        fprintf(dotFile, "   \"%d\" -> \"%d\";\n", i, parent->parent[i]);
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