#include "bellman_ford.h"

GrafoListaPonderado* criar_grafo(int vertices) {
    GrafoListaPonderado* g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = vertices;
    g->adj = (Aresta**) calloc(vertices, sizeof(Aresta*));
    return g;
}

void adicionar_aresta(GrafoListaPonderado* g, int u, int v, int peso) {
    Aresta* nova = (Aresta*) malloc(sizeof(Aresta));
    nova->destino = v;
    nova->peso = peso;
    nova->prox = g->adj[u];
    g->adj[u] = nova;
}

void liberar_grafo(GrafoListaPonderado* g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        Aresta* atual = g->adj[i];
        while (atual) {
            Aresta* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int n = g->num_vertices;

    // Inicialização
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[origem] = 0;

    // Relaxação das arestas (V - 1) vezes
    for (int i = 1; i <= n - 1; i++) {
        bool alterado = false;
        for (int u = 0; u < n; u++) {
            if (dist[u] == INF) continue;

            for (Aresta* e = g->adj[u]; e != NULL; e = e->prox) {
                int v = e->destino;
                if (dist[u] + e->peso < dist[v]) {
                    dist[v] = dist[u] + e->peso;
                    pred[v] = u;
                    alterado = true;
                }
            }
        }
        // Otimização: se nenhuma distância mudou, podemos parar antes
        if (!alterado) break;
    }

    // Checagem de Ciclos Negativos na V-ésima iteração
    for (int u = 0; u < n; u++) {
        if (dist[u] == INF) continue;

        for (Aresta* e = g->adj[u]; e != NULL; e = e->prox) {
            int v = e->destino;
            if (dist[u] + e->peso < dist[v]) {
                pred[v] = u; // Atualiza para garantir referência no ciclo
                printf("Ciclo negativo detectado a partir do vertice %d!\n", v);
                reconstruir_ciclo_negativo(v, pred, n);
                return 0; // Falha (ciclo negativo encontrado)
            }
        }
    }

    return 1; // Sucesso
}

void reconstruir_ciclo_negativo(int inicio_ciclo, int *pred, int num_vertices) {
    // Retrocede N vezes pelo pred[] para garantir que entramos dentro do ciclo
    int v = inicio_ciclo;
    for (int i = 0; i < num_vertices; i++) {
        v = pred[v];
    }

    // Armazena e imprime o ciclo
    int* ciclo = (int*) malloc((num_vertices + 1) * sizeof(int));
    int tam = 0;
    int curr = v;

    do {
        ciclo[tam++] = curr;
        curr = pred[curr];
    } while (curr != v && tam <= num_vertices);
    
    ciclo[tam++] = v; // Fecha o ciclo

    printf("Ciclo negativo reconstruido: ");
    for (int i = tam - 1; i >= 0; i--) {
        printf("%d%s", ciclo[i], (i == 0) ? "" : " -> ");
    }
    printf("\n");

    free(ciclo);
}