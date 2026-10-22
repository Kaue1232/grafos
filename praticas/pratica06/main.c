#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main() {
    int num_vertices = 5;
    GrafoListaPonderado* g = criar_grafo(num_vertices);

    // Grafo Exemplo:
    // 0 -> 1 (peso 4), 0 -> 2 (peso 2)
    // 1 -> 2 (peso 1), 1 -> 3 (peso 5)
    // 2 -> 3 (peso 8), 2 -> 4 (peso 10)
    // 3 -> 4 (peso 2)
    adicionar_aresta(g, 0, 1, 4);
    adicionar_aresta(g, 0, 2, 2);
    adicionar_aresta(g, 1, 2, 1);
    adicionar_aresta(g, 1, 3, 5);
    adicionar_aresta(g, 2, 3, 8);
    adicionar_aresta(g, 2, 4, 10);
    adicionar_aresta(g, 3, 4, 2);

    int dist[5];
    int pred[5];
    int origem = 0;

    dijkstra(g, origem, dist, pred);

    printf("Menores distâncias a partir do vértice %d:\n", origem);
    for (int i = 0; i < num_vertices; i++) {
        printf("Vértice %d: %d\n", i, dist[i]);
    }

    printf("\nCaminho mínimo até o vértice 4: ");
    reconstruir_caminho(origem, 4, pred);
    printf("\n");

    liberar_grafo(g);
    return 0;
}