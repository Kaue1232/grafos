#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"

GrafoMatriz* criar_grafo_matriz(int n) {
    GrafoMatriz *g = (GrafoMatriz*) malloc(sizeof(GrafoMatriz));
    if (!g) return NULL;

    g->num_vertices = n;
    g->matriz = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        g->matriz[i] = (int*) calloc(n, sizeof(int));
    }
    return g;
}

void inserir_aresta_matriz(GrafoMatriz *g, int u, int v) {
    if (g && u >= 0 && u < g->num_vertices && v >= 0 && v < g->num_vertices) {
        g->matriz[u][v] = 1;
        g->matriz[v][u] = 1; // Grafo não direcionado
    }
}

void remover_aresta_matriz(GrafoMatriz *g, int u, int v) {
    if (g && u >= 0 && u < g->num_vertices && v >= 0 && v < g->num_vertices) {
        g->matriz[u][v] = 0;
        g->matriz[v][u] = 0;
    }
}

int grau_matriz(GrafoMatriz *g, int v) {
    if (!g || v < 0 || v >= g->num_vertices) return -1;
    int grau = 0;
    for (int i = 0; i < g->num_vertices; i++) {
        if (g->matriz[v][i] == 1) grau++;
    }
    return grau;
}

int sao_adjacentes_matriz(GrafoMatriz *g, int u, int v) {
    if (!g || u < 0 || u >= g->num_vertices || v < 0 || v >= g->num_vertices) return 0;
    return g->matriz[u][v];
}

void liberar_grafo_matriz(GrafoMatriz *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        free(g->matriz[i]);
    }
    free(g->matriz);
    free(g);
}