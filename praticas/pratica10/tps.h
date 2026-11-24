#ifndef TPS_H
#define TPS_H

#include "hamiltoniano.h"

typedef struct {
    int n;
    int *custo;
} InstanciaTSP;

InstanciaTSP *tsp_criar(int n);
void tsp_destruir(InstanciaTSP *inst);

InstanciaTSP *grafo_para_tsp(const Grafo *g);

int tsp_forca_bruta(const InstanciaTSP *inst, int origem, int *rota);

int tsp_vizinho_mais_proximo(const InstanciaTSP *inst, int origem, int *rota);

int tsp_insercao(const InstanciaTSP *inst, int origem, int *rota);

#endif