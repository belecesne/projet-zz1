#include "../headers/dijkstra.h"


file_t *dijkstra(labyrinthe_t *labyrinthe, noeud_t rac, noeud_t dest) {
    file_t *file = creer_file();
    int *d = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
    int *parent = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
    tas_dijkstra_t *tas = creerTasDijktra();
    noeud_t *voisins, voisinAct;
    int i;
    for (i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
        if (i == rac) {
            d[i] = 0;
            ajoutTasDijkstra(tas, i, d[i]);
        } else {
            d[i] = INT_MAX;
        }
        parent[i] = -1;
    }
    printf("1\n");
    elem_tas_dijkstra_t e = suppressionRacineDijkstra(tas);
    printf("2\n");
    while (e.som != dest) {
        enfiler(file, e.som);
        voisins = obtenirVoisins(labyrinthe, e.som);
        printf("Voisin de %d :\n", e.som);
        for (i = 0; i < 4; i++) {
            voisinAct = voisins[i];
            printf("%d",voisinAct);
            if (voisinAct != -1 && d[voisinAct] != INT_MAX) {
                d[voisinAct] = d[e.som] + 1;
                parent[voisinAct] = e.som;
                printf("Voisin %d - Distance : %d\n", voisinAct, d[voisinAct]);
                ajoutTasDijkstra(tas, voisinAct, d[voisinAct]);
                printf("-----------------\n");
            }
        }
        e = suppressionRacineDijkstra(tas);
        free(voisins);
    }
    enfiler(file, dest);
    libererTasDijkstra(tas);
    free(d);
    free(parent);
    return file;
}
