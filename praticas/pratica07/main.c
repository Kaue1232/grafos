#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

int main() {
    int n = 4;
    GrafoListaPonderado* g = criar_grafo(n);

    // Grafo de exemplo com um ciclo negativo (1 -> 2 -> 3 -> 1 com custo total = -1)
    adicionar_aresta(g, 0, 1, 4);
    adicionar_aresta(g, 1, 2, 2);
    adicionar_aresta(g, 2, 3, -6);
    adicionar_aresta(g, 3, 1, 3);

    int dist[4];
    int pred[4];
    int origem = 0;

    printf("Executando Bellman-Ford a partir da origem %d...\n", origem);
    int resultado = bellman_ford(g, origem, dist, pred);

    if (resultado == 1) {
        printf("\nCaminhos minimos sem ciclos negativos:\n");
        for (int i = 0; i < n; i++) {
            printf("Vertice %d: Distancia = %d, Predecessor = %d\n", i, dist[i], pred[i]);
        }
    }

    liberar_grafo(g);
    return 0;
}