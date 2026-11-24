#include "tps.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

InstanciaTSP *tsp_criar(int n) {
    if (n <= 0) return NULL;
    InstanciaTSP *inst = (InstanciaTSP *)malloc(sizeof(InstanciaTSP));
    if (!inst) return NULL;
    inst->n = n;
    inst->custo = (int *)calloc((size_t)n * (size_t)n, sizeof(int));
    if (!inst->custo) {
        free(inst);
        return NULL;
    }
    return inst;
}

void tsp_destruir(InstanciaTSP *inst) {
    if (!inst) return;
    free(inst->custo);
    free(inst);
}

InstanciaTSP *grafo_para_tsp(const Grafo *g) {
    if (!g) return NULL;
    InstanciaTSP *inst = tsp_criar(g->n);
    if (!inst) return NULL;

    const int n = g->n;
    const int * restrict adj = g->adj;
    int * restrict custo = inst->custo;

    for (int i = 0; i < n; ++i) {
        const int base = i * n;
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                custo[base + j] = 0;
            } else {
                custo[base + j] = (adj[base + j] != 0) ? 1 : 2;
            }
        }
    }
    return inst;
}

static void fb_dfs(const InstanciaTSP *inst, int origem, int atual, int pos,
                   int custo_acum, int *melhor_custo, int *rota_atual,
                   int *melhor_rota, unsigned char *visitado) {
    const int n = inst->n;
    const int * restrict custo = inst->custo;

    if (custo_acum >= *melhor_custo) return;

    if (pos == n) {
        const int volta = custo[atual * n + origem];
        if (volta < INT_MAX - custo_acum) {
            const int total = custo_acum + volta;
            if (total < *melhor_custo) {
                *melhor_custo = total;
                memcpy(melhor_rota, rota_atual, (size_t)n * sizeof(int));
            }
        }
        return;
    }

    const int row = atual * n;
    for (int prox = 0; prox < n; ++prox) {
        if (!visitado[prox]) {
            const int w = custo[row + prox];
            if (w < INT_MAX - custo_acum && (custo_acum + w) < *melhor_custo) {
                visitado[prox] = 1;
                rota_atual[pos] = prox;

                fb_dfs(inst, origem, prox, pos + 1, custo_acum + w,
                       melhor_custo, rota_atual, melhor_rota, visitado);

                visitado[prox] = 0;
            }
        }
    }
}

int tsp_forca_bruta(const InstanciaTSP *inst, int origem, int *rota) {
    if (!inst || !rota || origem < 0 || origem >= inst->n) return INT_MAX;

    const int n = inst->n;
    if (n == 1) {
        rota[0] = origem;
        return inst->custo[0];
    }

    unsigned char *visitado = (unsigned char *)calloc((size_t)n, sizeof(unsigned char));
    int *rota_atual = (int *)malloc((size_t)n * sizeof(int));
    if (!visitado || !rota_atual) {
        free(visitado);
        free(rota_atual);
        return INT_MAX;
    }

    int melhor_custo = INT_MAX;
    rota_atual[0] = origem;
    visitado[origem] = 1;

    fb_dfs(inst, origem, origem, 1, 0, &melhor_custo, rota_atual, rota, visitado);

    free(visitado);
    free(rota_atual);
    return melhor_custo;
}

int tsp_vizinho_mais_proximo(const InstanciaTSP *inst, int origem, int *rota) {
    if (!inst || !rota || origem < 0 || origem >= inst->n) return INT_MAX;

    const int n = inst->n;
    if (n == 1) {
        rota[0] = origem;
        return inst->custo[0];
    }

    unsigned char *visitado = (unsigned char *)calloc((size_t)n, sizeof(unsigned char));
    if (!visitado) return INT_MAX;

    const int * restrict custo = inst->custo;
    int atual = origem;
    int custo_total = 0;

    rota[0] = origem;
    visitado[origem] = 1;

    for (int passo = 1; passo < n; ++passo) {
        int melhor_prox = -1;
        int menor_w = INT_MAX;
        const int row = atual * n;

        for (int v = 0; v < n; ++v) {
            if (!visitado[v] && custo[row + v] < menor_w) {
                menor_w = custo[row + v];
                melhor_prox = v;
            }
        }

        if (melhor_prox == -1 || menor_w == INT_MAX) {
            free(visitado);
            return INT_MAX;
        }

        visitado[melhor_prox] = 1;
        rota[passo] = melhor_prox;
        custo_total += menor_w;
        atual = melhor_prox;
    }

    const int volta = custo[atual * n + origem];
    free(visitado);

    if (volta == INT_MAX) return INT_MAX;
    return custo_total + volta;
}

int tsp_insercao(const InstanciaTSP *inst, int origem, int *rota) {
    if (!inst || !rota || origem < 0 || origem >= inst->n) return INT_MAX;

    const int n = inst->n;
    if (n == 1) {
        rota[0] = origem;
        return inst->custo[0];
    }

    unsigned char *na_rota = (unsigned char *)calloc((size_t)n, sizeof(unsigned char));
    int *ciclo = (int *)malloc((size_t)(n + 1) * sizeof(int));
    if (!na_rota || !ciclo) {
        free(na_rota);
        free(ciclo);
        return INT_MAX;
    }

    const int * restrict custo = inst->custo;


    int segundo = -1;
    int menor_ini = INT_MAX;
    for (int v = 0; v < n; ++v) {
        if (v != origem && custo[origem * n + v] < menor_ini) {
            menor_ini = custo[origem * n + v];
            segundo = v;
        }
    }

    if (segundo == -1 || menor_ini == INT_MAX) {
        free(na_rota);
        free(ciclo);
        return INT_MAX;
    }

    ciclo[0] = origem;
    ciclo[1] = segundo;
    ciclo[2] = origem;
    na_rota[origem] = 1;
    na_rota[segundo] = 1;

    int tam_ciclo = 2; 

    while (tam_ciclo < n) {
  
        int k_escolhido = -1;
        int menor_dist = INT_MAX;

        for (int k = 0; k < n; ++k) {
            if (na_rota[k]) continue;
            for (int idx = 0; idx < tam_ciclo; ++idx) {
                const int c_node = ciclo[idx];
                const int d1 = custo[c_node * n + k];
                const int d2 = custo[k * n + c_node];
                const int d = (d1 < d2) ? d1 : d2;
                if (d < menor_dist) {
                    menor_dist = d;
                    k_escolhido = k;
                }
            }
        }

        if (k_escolhido == -1) {
            free(na_rota);
            free(ciclo);
            return INT_MAX;
        }

        int melhor_pos = 1;
        int menor_delta = INT_MAX;

        for (int i = 0; i < tam_ciclo; ++i) {
            const int u = ciclo[i];
            const int v = ciclo[i + 1];
            const int c_uv = custo[u * n + v];
            const int c_uk = custo[u * n + k_escolhido];
            const int c_kv = custo[k_escolhido * n + v];

            if (c_uv < INT_MAX && c_uk < INT_MAX && c_kv < INT_MAX) {
                const int delta = c_uk + c_kv - c_uv;
                if (delta < menor_delta) {
                    menor_delta = delta;
                    melhor_pos = i + 1;
                }
            }
        }

        memmove(&ciclo[melhor_pos + 1], &ciclo[melhor_pos],
                (size_t)(tam_ciclo + 1 - melhor_pos) * sizeof(int));
        ciclo[melhor_pos] = k_escolhido;
        na_rota[k_escolhido] = 1;
        tam_ciclo++;
    }

    memcpy(rota, ciclo, (size_t)n * sizeof(int));

    int custo_total = 0;
    for (int i = 0; i < n; ++i) {
        custo_total += custo[ciclo[i] * n + ciclo[i + 1]];
    }

    free(na_rota);
    free(ciclo);
    return custo_total;
}