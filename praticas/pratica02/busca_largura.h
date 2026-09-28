#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include <stdbool.h>


typedef struct No {
    int vizinho;
    struct No *prox;
} No;

typedef struct {
    int num_vertices;
    No **adj;
} GrafoLista;


typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;


Fila* criar_fila(int capacidade);
void destruir_fila(Fila *f);
bool fila_vazia(Fila *f);
void enfileirar(Fila *f, int v);
int desenfileirar(Fila *f);


void bfs(GrafoLista *g, int origem, int *dist, int *pred);
bool eh_bipartido(GrafoLista *g);

#endif