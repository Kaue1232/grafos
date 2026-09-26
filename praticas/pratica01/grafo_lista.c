#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista* criar_grafo_lista(int n) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    if (!g) return NULL;

    g->num_vertices = n;
    g->listas = (No**) malloc(n * sizeof(No*));
    for (int i = 0; i < n; i++) {
        g->listas[i] = NULL;
    }
    return g;
}

static void aux_inserir(GrafoLista *g, int u, int v) {
    No *novo = (No*) malloc(sizeof(No));
    novo->vertice = v;
    novo->prox = g->listas[u];
    g->listas[u] = novo;
}

void inserir_aresta_lista(GrafoLista *g, int u, int v) {
    if (!g || u < 0 || u >= g->num_vertices || v < 0 || v >= g->num_vertices) return;
    if (sao_adjacentes_lista(g, u, v)) return; // Evita arestas duplicadas

    aux_inserir(g, u, v);
    aux_inserir(g, v, u); // Grafo não direcionado
}

static void aux_remover(GrafoLista *g, int u, int v) {
    No *atual = g->listas[u];
    No *anterior = NULL;

    while (atual && atual->vertice != v) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual) {
        if (anterior) anterior->prox = atual->prox;
        else g->listas[u] = atual->prox;
        free(atual);
    }
}

void remover_aresta_lista(GrafoLista *g, int u, int v) {
    if (!g || u < 0 || u >= g->num_vertices || v < 0 || v >= g->num_vertices) return;
    aux_remover(g, u, v);
    aux_remover(g, v, u);
}

int grau_lista(GrafoLista *g, int v) {
    if (!g || v < 0 || v >= g->num_vertices) return -1;
    int grau = 0;
    No *atual = g->listas[v];
    while (atual) {
        grau++;
        atual = atual->prox;
    }
    return grau;
}

int sao_adjacentes_lista(GrafoLista *g, int u, int v) {
    if (!g || u < 0 || u >= g->num_vertices || v < 0 || v >= g->num_vertices) return 0;
    No *atual = g->listas[u];
    while (atual) {
        if (atual->vertice == v) return 1;
        atual = atual->prox;
    }
    return 0;
}

void liberar_grafo_lista(GrafoLista *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->listas[i];
        while (atual) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->listas);
    free(g);
}