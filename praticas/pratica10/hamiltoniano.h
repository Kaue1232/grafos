#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int n;
    int *adj;
} Grafo;

Grafo *grafo_criar(int n);
void grafo_destruir(Grafo *g);

bool encontrar_caminho_hamiltoniano_bt(const Grafo *g, int inicio, int *caminho, bool fechar_ciclo);

bool encontrar_ciclo_hamiltoniano_bt(const Grafo *g, int inicio, int *caminho);

#endif