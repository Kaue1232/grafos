#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define INF INT_MAX

// Nó da lista de adjacência
typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta* prox;
} Aresta;

// Estrutura do Grafo com Lista de Adjacência Ponderada
typedef struct {
    int num_vertices;
    Aresta** adj;
} GrafoListaPonderado;

// Protótipos das funções
GrafoListaPonderado* criar_grafo(int vertices);
void adicionar_aresta(GrafoListaPonderado* g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado* g);

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_ciclo_negativo(int inicio_ciclo, int *pred, int num_vertices);

#endif