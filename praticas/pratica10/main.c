#include "hamiltoniano.h"
#include "tps.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32)
#include <windows.h>
static double agora_ms(void) {
    static LARGE_INTEGER freq;
    static int inicializado = 0;
    if (!inicializado) {
        QueryPerformanceFrequency(&freq);
        inicializado = 1;
    }
    LARGE_INTEGER contador;
    QueryPerformanceCounter(&contador);
    return (double)contador.QuadPart * 1000.0 / (double)freq.QuadPart;
}
#else
static double agora_ms(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ((double)ts.tv_sec * 1000.0) + ((double)ts.tv_nsec / 1e6);
}
#endif

static void preencher_instancia_aleatoria(InstanciaTSP *inst, unsigned int seed) {
    srand(seed);
    const int n = inst->n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                inst->custo[i * n + j] = 0;
            } else {
                inst->custo[i * n + j] = 1 + (rand() % 100);
            }
        }
    }
}

static void testar_hamiltoniano_e_reducao(void) {
    const int n = 6;
    Grafo *g = grafo_criar(n);
    if (!g) return;

    for (int i = 0; i < n; ++i) {
        int prox = (i + 1) % n;
        g->adj[i * n + prox] = 1;
        g->adj[prox * n + i] = 1;
    }
    g->adj[0 * n + 3] = 1;
    g->adj[3 * n + 0] = 1;

    int *caminho = (int *)malloc((size_t)n * sizeof(int));
    int *ciclo = (int *)malloc((size_t)n * sizeof(int));

    if (encontrar_caminho_hamiltoniano_bt(g, 0, caminho, false)) {
        printf("Caminho Hamiltoniano encontrado: ");
        for (int i = 0; i < n; ++i) {
            printf("%d%s", caminho[i], (i + 1 < n) ? " -> " : "\n");
        }
    }

    if (encontrar_ciclo_hamiltoniano_bt(g, 0, ciclo)) {
        printf("Ciclo Hamiltoniano encontrado:   ");
        for (int i = 0; i < n; ++i) {
            printf("%d -> ", ciclo[i]);
        }
        printf("%d\n", ciclo[0]);
    }

    InstanciaTSP *red = grafo_para_tsp(g);
    if (red) {
        int *rota_red = (int *)malloc((size_t)n * sizeof(int));
        int custo_red = tsp_forca_bruta(red, 0, rota_red);
        printf("Reducao Grafo->TSP (n=%d): custo minimo = %d (esperado = %d se ha ciclo)\n",
               n, custo_red, n);
        free(rota_red);
        tsp_destruir(red);
    }

    free(caminho);
    free(ciclo);
    grafo_destruir(g);
}

int main(void) {
    testar_hamiltoniano_e_reducao();

    printf("\n=== Experimento TSP (n = 5, 8, 10, 12) ===\n");
    printf("%-4s | %-12s %-11s | %-12s %-11s | %-12s %-11s\n",
           "n", "FB Custo", "FB (ms)", "VMP Custo", "VMP (ms)", "Ins Custo", "Ins (ms)");
    printf("--------------------------------------------------------------------------------\n");

    const int tamanhos[] = {5, 8, 10, 12};
    const int qtd_tamanhos = (int)(sizeof(tamanhos) / sizeof(tamanhos[0]));

    for (int idx = 0; idx < qtd_tamanhos; ++idx) {
        const int n = tamanhos[idx];
        InstanciaTSP *inst = tsp_criar(n);
        int *rota_fb = (int *)malloc((size_t)n * sizeof(int));
        int *rota_vmp = (int *)malloc((size_t)n * sizeof(int));
        int *rota_ins = (int *)malloc((size_t)n * sizeof(int));

        preencher_instancia_aleatoria(inst, (unsigned int)(1000 + n));

        double t0, t1;

        t0 = agora_ms();
        int custo_fb = tsp_forca_bruta(inst, 0, rota_fb);
        t1 = agora_ms();
        double ms_fb = t1 - t0;

        t0 = agora_ms();
        int custo_vmp = tsp_vizinho_mais_proximo(inst, 0, rota_vmp);
        t1 = agora_ms();
        double ms_vmp = t1 - t0;

        t0 = agora_ms();
        int custo_ins = tsp_insercao(inst, 0, rota_ins);
        t1 = agora_ms();
        double ms_ins = t1 - t0;

        printf("%-4d | %-12d %-11.4f | %-12d %-11.4f | %-12d %-11.4f\n",
               n, custo_fb, ms_fb, custo_vmp, ms_vmp, custo_ins, ms_ins);

        free(rota_fb);
        free(rota_vmp);
        free(rota_ins);
        tsp_destruir(inst);
    }

    return 0;
}