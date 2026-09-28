#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"
#include "busca_profundidade.h"


GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->adj = (No**) malloc(num_vertices * sizeof(No*));
    for (int i = 0; i < num_vertices; i++) {
        g->adj[i] = NULL;
    }
    return g;
}


void adicionar_aresta(GrafoLista *g, int u, int v) {
    No *novo = (No*) malloc(sizeof(No));
    novo->vizinho = v;
    novo->prox = g->adj[u];
    g->adj[u] = novo;

    novo = (No*) malloc(sizeof(No));
    novo->vizinho = u;
    novo->prox = g->adj[v];
    g->adj[v] = novo;
}

int main() {
    int n = 5;
    GrafoLista *g = criar_grafo(n);

   
    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 1, 2);
    adicionar_aresta(g, 0, 3);
    adicionar_aresta(g, 1, 4);

    int dist[5], pred[5];
    bfs(g, 0, dist, pred);

    printf("--- Distâncias a partir do vértice 0 (BFS) ---\n");
    for (int i = 0; i < n; i++) {
        printf("Vertice %d: distancia = %d, predecessor = %d\n", i, dist[i], pred[i]);
    }

    printf("\n--- Analise do Grafo ---\n");
    printf("Componentes conexos: %d\n", contar_componentes(g));
    printf("Possui ciclo? %s\n", tem_ciclo(g) ? "Sim" : "Não");
    printf("E bipartido? %s\n", eh_bipartido(g) ? "Sim" : "Não");

    return 0;
}