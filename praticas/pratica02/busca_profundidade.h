#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include <stdbool.h>
#include "busca_largura.h" 


typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;


Pilha* criar_pilha(int capacidade);
void destruir_pilha(Pilha *p);
bool pilha_vazia(Pilha *p);
void empilhar(Pilha *p, int v);
int desempilhar(Pilha *p);


void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pai);
int contar_componentes(GrafoLista *g);
bool tem_ciclo(GrafoLista *g);

#endif