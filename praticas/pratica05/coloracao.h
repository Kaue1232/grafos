
#ifndef COLORACAO_H
#define COLORACAO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para lista de adjacência de Grafo
typedef struct No {
    int vertice;
    struct No* proximo;
} No;

typedef struct GrafoLista {
    int num_vertices;
    No** listas;
} GrafoLista;

// Protótipos das funções do grafo
GrafoLista* criar_grafo(int vertices);
void adicionar_aresta(GrafoLista* g, int u, int v);
void liberar_grafo(GrafoLista* g);

// Protótipos solicitados na Prática 05
int* coloracao_gulosa(GrafoLista *g, int *num_cores);
int* coloracao_welsh_powell(GrafoLista *g, int *num_cores);
bool eh_bipartido(GrafoLista *g);

#endif