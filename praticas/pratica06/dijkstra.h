#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// Estrutura de nó de adjacência para o grafo
typedef struct No {
    int destino;
    int peso;
    struct No* proximo;
} No;

// Grafo representado como Lista de Adjascência Ponderada
typedef struct {
    int num_vertices;
    No** listas;
} GrafoListaPonderado;

// Estruturas obrigatórias solicitadas
typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; // mapeia vértice -> índice no heap
} MinHeap;

// Protótipos das Funções do MinHeap
MinHeap* criar_min_heap(int capacidade);
void liberar_min_heap(MinHeap* heap);
NoHeap extrair_minimo(MinHeap* heap);
void diminuir_chave(MinHeap* heap, int vertice, int nova_distancia);

// Protótipos do Algoritmo de Dijkstra e Auxiliares
GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado* g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado* g);

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif