#ifndef COBERTURA_H
#define COBERTURA_H

#include <stdbool.h>

#define MAX_V 30

typedef struct {
    int num_v;
    int adj[MAX_V][MAX_V];
} Grafo;


Grafo* criar_grafo(int n);
void liberar_grafo(Grafo* g);
void adicionar_aresta(Grafo* g, int u, int v);
Grafo* gerar_grafo_aleatorio(int n, double p);


bool eh_cobertura(const Grafo* g, const bool* solucao);
int cobertura_minima_bt(const Grafo* g, bool* melhor_solucao);
int cobertura_gulosa(const Grafo* g, bool* solucao);

#endif