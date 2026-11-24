#include "hamiltoniano.h"
#include <stdlib.h>
#include <string.h>

Grafo *grafo_criar(int n) {
    if (n <= 0) return NULL;
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    if (!g) return NULL;
    g->n = n;
    g->adj = (int *)calloc((size_t)n * (size_t)n, sizeof(int));
    if (!g->adj) {
        free(g);
        return NULL;
    }
    return g;
}

void grafo_destruir(Grafo *g) {
    if (!g) return;
    free(g->adj);
    free(g);
}

static bool bt_dfs(const Grafo *g, int atual, int pos, bool fechar_ciclo,
                   int *caminho, unsigned char *visitado) {
    const int n = g->n;
    const int * restrict adj = g->adj;

    if (pos == n) {
        if (!fechar_ciclo) return true;
        return adj[atual * n + caminho[0]] != 0;
    }

    const int row_offset = atual * n;
    for (int prox = 0; prox < n; ++prox) {
        if (!visitado[prox] && adj[row_offset + prox] != 0) {
            visitado[prox] = 1;
            caminho[pos] = prox;

            if (bt_dfs(g, prox, pos + 1, fechar_ciclo, caminho, visitado)) {
                return true;
            }

            visitado[prox] = 0;
        }
    }
    return false;
}

bool encontrar_caminho_hamiltoniano_bt(const Grafo *g, int inicio, int *caminho, bool fechar_ciclo) {
    if (!g || !caminho || inicio < 0 || inicio >= g->n) return false;

    const int n = g->n;
    if (n == 1) {
        caminho[0] = inicio;
        return !fechar_ciclo || (g->adj[0] != 0);
    }

    unsigned char *visitado = (unsigned char *)calloc((size_t)n, sizeof(unsigned char));
    if (!visitado) return false;

    caminho[0] = inicio;
    visitado[inicio] = 1;

    bool achou = bt_dfs(g, inicio, 1, fechar_ciclo, caminho, visitado);

    free(visitado);
    return achou;
}

bool encontrar_ciclo_hamiltoniano_bt(const Grafo *g, int inicio, int *caminho) {
    return encontrar_caminho_hamiltoniano_bt(g, inicio, caminho, true);
}