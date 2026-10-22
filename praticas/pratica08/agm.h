#ifndef AGM_H
#define AGM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Estruturas Obrigatórias
typedef struct {
    int *pai, *rank;
    int n;
} DSU;

typedef struct {
    int u, v, peso;
} Aresta;

// Estruturas auxiliares para o algoritmo de Prim (Lista de Adjacência e Min-Heap)
typedef struct NoAdj {
    int v;
    int peso;
    struct NoAdj* prox;
} NoAdj;

typedef struct {
    NoAdj** cabecas;
    int V;
} Grafo;

typedef struct {
    int v;
    int chave;
} ElementoHeap;

typedef struct {
    int *pos; // Posição do vértice no heap para atualização $O(\log V)$
    ElementoHeap *array;
    int tamanho;
    int capacidade;
} MinHeap;

// Protótipos DSU / Kruskal
DSU* criarDSU(int n);
void destruirDSU(DSU *d);
int find(DSU *d, int x);
bool unir(DSU *d, int x, int y);
int kruskal(int V, Aresta *arestas, int E);

// Protótipos Prim / Grafo / Heap
Grafo* criarGrafo(int V);
void adicionarAresta(Grafo* g, int u, int v, int peso);
void destruirGrafo(Grafo* g);
int prim(Grafo* g, int origem);

#endif