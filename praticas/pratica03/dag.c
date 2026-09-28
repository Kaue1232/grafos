#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dag.h"

typedef struct {
    int *dados;
    int inicio, fim, capacidade, tamanho;
} Fila;

static Fila* criar_fila(int cap) {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->dados = (int*) malloc(cap * sizeof(int));
    f->inicio = 0;
    f->fim = 0;
    f->capacidade = cap;
    f->tamanho = 0;
    return f;
}

static void enfileirar(Fila *f, int v) {
    if (f->tamanho == f->capacidade) return;
    f->dados[f->fim] = v;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}

static int desenfileirar(Fila *f) {
    if (f->tamanho == 0) return -1;
    int v = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return v;
}

static void destruir_fila(Fila *f) {
    if (f) {
        free(f->dados);
        free(f);
    }
}

GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->adj = (No**) malloc(num_vertices * sizeof(No*));
    for (int i = 0; i < num_vertices; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

void adicionar_aresta_dirigida(GrafoLista *g, int u, int v) {
    No *novo = (No*) malloc(sizeof(No));
    novo->vizinho = v;
    novo->prox = g->adj[u];
    g->adj[u] = novo;
}

void destruir_grafo(GrafoLista *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->adj[i];
        while (atual) {
            No *tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}


int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int n = g->num_vertices;
    int *grau_entrada = (int*) calloc(n, sizeof(int));

    for (int u = 0; u < n; u++) {
        No *atual = g->adj[u];
        while (atual != NULL) {
            grau_entrada[atual->vizinho]++;
            atual = atual->prox;
        }
    }

    Fila *f = criar_fila(n);
    for (int i = 0; i < n; i++) {
        if (grau_entrada[i] == 0) {
            enfileirar(f, i);
        }
    }

    int *resultado = (int*) malloc(n * sizeof(int));
    int count = 0;

    while (f->tamanho > 0) {
        int u = desenfileirar(f);
        resultado[count++] = u;

        No *atual = g->adj[u];
        while (atual != NULL) {
            int v = atual->vizinho;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) {
                enfileirar(f, v);
            }
            atual = atual->prox;
        }
    }

    destruir_fila(f);
    free(grau_entrada);

    
    if (count < n) {
        free(resultado);
        *tamanho = 0;
        return NULL; 
    }

    *tamanho = count;
    return resultado;
}

static bool dfs_ordem_topologica(GrafoLista *g, int u, int *cor, int *pilha_saida, int *topo_pilha) {
    cor[u] = 1; 

    No *atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->vizinho;
        if (cor[v] == 1) {
            return false; 
        }
        if (cor[v] == 0) {
            if (!dfs_ordem_topologica(g, v, cor, pilha_saida, topo_pilha)) {
                return false;
            }
        }
        atual = atual->prox;
    }

    cor[u] = 2; 
    pilha_saida[(*topo_pilha)--] = u; 
    return true;
}


int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    int n = g->num_vertices;
    int *cor = (int*) calloc(n, sizeof(int));
    int *resultado = (int*) malloc(n * sizeof(int));
    int topo_pilha = n - 1; 

    for (int i = 0; i < n; i++) {
        if (cor[i] == 0) {
            if (!dfs_ordem_topologica(g, i, cor, resultado, &topo_pilha)) {
                free(cor);
                free(resultado);
                *tamanho = 0;
                return NULL; 
            }
        }
    }

    free(cor);
    *tamanho = n;
    return resultado;
}


bool eh_dag(GrafoLista *g) {
    int tamanho = 0;
    int *res = ordenacao_topologica_kahn(g, &tamanho);
    if (res != NULL) {
        free(res);
        return true;
    }
    return false;
}