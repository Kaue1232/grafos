
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "busca_profundidade.h"

Pilha* criar_pilha(int capacidade) {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    p->dados = (int*) malloc(capacidade * sizeof(int));
    p->topo = -1;
    p->capacidade = capacidade;
    return p;
}

void destruir_pilha(Pilha *p) {
    if (p) {
        free(p->dados);
        free(p);
    }
}

bool pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, int v) {
    if (p->topo < p->capacidade - 1) {
        p->dados[++(p->topo)] = v;
    }
}

int desempilhar(Pilha *p) {
    if (pilha_vazia(p)) return -1;
    return p->dados[(p->topo)--];
}


void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pai) {
    visitado[u] = 1;

    No *atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->vizinho;
        if (!visitado[v]) {
            if (pai != NULL) pai[v] = u;
            dfs_recursiva(g, v, visitado, pai);
        }
        atual = atual->prox;
    }
}


int contar_componentes(GrafoLista *g) {
    int *visitado = (int*) calloc(g->num_vertices, sizeof(int));
    int componentes = 0;

    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            componentes++;
            dfs_recursiva(g, i, visitado, NULL);
        }
    }

    free(visitado);
    return componentes;
}


static bool tem_ciclo_dfs(GrafoLista *g, int u, int *visitado, int pai) {
    visitado[u] = 1;

    No *atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->vizinho;

        if (!visitado[v]) {
            if (tem_ciclo_dfs(g, v, visitado, u)) return true;
        } else if (v != pai) {
            return true; 
        }
        atual = atual->prox;
    }
    return false;
}


bool tem_ciclo(GrafoLista *g) {
    int *visitado = (int*) calloc(g->num_vertices, sizeof(int));

    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            if (tem_ciclo_dfs(g, i, visitado, -1)) {
                free(visitado);
                return true;
            }
        }
    }

    free(visitado);
    return false;
}