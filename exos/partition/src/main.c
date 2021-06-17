#include "../headers/union_find.h"


int main() {
    int erreur = 0;
    union_find_t *unionFind;
    unionFind = createUnionFind(DEFAULT_UNION_FIND_SIZE, &erreur);
    if (!erreur) {
        initUnionFind(unionFind);
        printUnionFind(unionFind);


        fusionUnionFind(unionFind, 0, 1);
        printUnionFind(unionFind);

        fusionUnionFind(unionFind, 2, 3);
        printUnionFind(unionFind);

        fusionUnionFind(unionFind, 10, 3);
        printUnionFind(unionFind);

        fusionUnionFind(unionFind, 5, 9);
        printUnionFind(unionFind);

        fusionUnionFind(unionFind, 4, 6);
        printUnionFind(unionFind);


        fusionUnionFind(unionFind, 8, 7);
        printUnionFind(unionFind);


        fusionUnionFind(unionFind, 7, 9);
        printUnionFind(unionFind);


        fusionUnionFind(unionFind, 6, 8);
        printUnionFind(unionFind);

        printClassUnionFind(unionFind,3);
        printAllClassesUnionFind(unionFind);
        makeGraphvizGraph(unionFind, "graph");
        freeUnionFind(unionFind);
    }

    return 0;
}

