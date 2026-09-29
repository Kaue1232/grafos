#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

int main() {
    printf("=== TESTE PRATICA 05: COLORACAO DE GRAFOS ===\n\n");

    // Criando um grafo de teste (Cíclico com 5 vértices: C5)
    GrafoLista* g = criar_grafo(5);
    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 1, 2);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 3, 4);
    adicionar_aresta(g, 4, 0);

    int num_cores_gulosa = 0;
    int* cores_gulosa = coloracao_gulosa(g, &num_cores_gulosa);

    printf("1. Coloraçao Gulosa:\n");
    printf("   Numero de cores usadas: %d\n", num_cores_gulosa);
    for (int i = 0; i < g->num_vertices; i++) {
        printf("   Vertice %d -> Cor %d\n", i, cores_gulosa[i]);
    }

    int num_cores_wp = 0;
    int* cores_wp = coloracao_welsh_powell(g, &num_cores_wp);

    printf("\n2. Coloraçao Welsh-Powell:\n");
    printf("   Numero de cores usadas: %d\n", num_cores_wp);
    for (int i = 0; i < g->num_vertices; i++) {
        printf("   Vertice %d -> Cor %d\n", i, cores_wp[i]);
    }

    printf("\n3. Verificação de Bipartido:\n");
    if (eh_bipartido(g)) {
        printf("   O grafo E bipartido (2-coloravel).\n");
    } else {
        printf("   O grafo NAO E bipartido.\n");
    }

    free(cores_gulosa);
    free(cores_wp);
    liberar_grafo(g);

    return 0;
}