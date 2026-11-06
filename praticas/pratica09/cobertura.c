#include <stdio.h>
#include <stdlib.h>
#include "cobertura.h"


Grafo* criar_grafo(int n) {
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    g->num_v = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->adj[i][j] = 0;
        }
    }
    return g;
}

void liberar_grafo(Grafo* g) {
    free(g);
}

void adicionar_aresta(Grafo* g, int u, int v) {
    if (u >= 0 && u < g->num_v && v >= 0 && v < g->num_v && u != v) {
        g->adj[u][v] = 1;
        g->adj[v][u] = 1;
    }
}

Grafo* gerar_grafo_aleatorio(int n, double p) {
    Grafo* g = criar_grafo(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((double) rand() / RAND_MAX < p) {
                adicionar_aresta(g, i, j);
            }
        }
    }
    return g;
}

bool eh_cobertura(const Grafo* g, const bool* solucao) {
    for (int i = 0; i < g->num_v; i++) {
        for (int j = i + 1; j < g->num_v; j++) {
            if (g->adj[i][j] && !solucao[i] && !solucao[j]) {
                return false; 
            }
        }
    }
    return true;
}

static void bt_aux(const Grafo* g, int v, bool* sol_atual, int tam_atual, bool* mel_sol, int* mel_tam) {
    if (tam_atual >= *mel_tam) {
        return;
    }

    if (v == g->num_v) {
        if (eh_cobertura(g, sol_atual)) {
            *mel_tam = tam_atual;
            for (int i = 0; i < g->num_v; i++) {
                mel_sol[i] = sol_atual[i];
            }
        }
        return;
    }

    sol_atual[v] = true;
    bt_aux(g, v + 1, sol_atual, tam_atual + 1, mel_sol, mel_tam);

    sol_atual[v] = false;
    bt_aux(g, v + 1, sol_atual, tam_atual, mel_sol, mel_tam);
}

int cobertura_minima_bt(const Grafo* g, bool* melhor_solucao) {
    bool solucao_atual[MAX_V] = {false};
    int melhor_tamanho = g->num_v + 1;

    bt_aux(g, 0, solucao_atual, 0, melhor_solucao, &melhor_tamanho);
    return melhor_tamanho;
}

int cobertura_gulosa(const Grafo* g, bool* solucao) {
    int temp_adj[MAX_V][MAX_V];
    for (int i = 0; i < g->num_v; i++) {
        solucao[i] = false;
        for (int j = 0; j < g->num_v; j++) {
            temp_adj[i][j] = g->adj[i][j];
        }
    }

    int tamanho = 0;

    while (1) {
        int max_grau = 0;
        int melhor_v = -1;

        for (int i = 0; i < g->num_v; i++) {
            if (solucao[i]) continue;

            int grau = 0;
            for (int j = 0; j < g->num_v; j++) {
                if (temp_adj[i][j]) grau++;
            }

            if (grau > max_grau) {
                max_grau = grau;
                melhor_v = i;
            }
        }

        if (max_grau == 0 || melhor_v == -1) break;

        solucao[melhor_v] = true;
        tamanho++;

        for (int j = 0; j < g->num_v; j++) {
            temp_adj[melhor_v][j] = 0;
            temp_adj[j][melhor_v] = 0;
        }
    }

    return tamanho;
}