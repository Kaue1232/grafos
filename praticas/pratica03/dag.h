#ifndef DAG_H
#define DAG_H

#include <stdbool.h>


typedef struct No {
    int vizinho;
    struct No *prox;
} No;

typedef struct {
    int num_vertices;
    No **adj;
} GrafoLista;

GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta_dirigida(GrafoLista *g, int u, int v);
void destruir_grafo(GrafoLista *g);

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);
int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);
bool eh_dag(GrafoLista *g);

#endif