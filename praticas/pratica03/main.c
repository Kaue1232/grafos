#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

void imprimir_ordem(const char *metodo, int *ordem, int tamanho) {
    if (ordem == NULL) {
        printf("%s: O grafo possui ciclo! Nao e um DAG.\n", metodo);
    } else {
        printf("%s: ", metodo);
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", ordem[i]);
        }
        printf("\n");
    }
}

int main() {
    printf("=== Teste 1: Grafo Aciclico (DAG) ===\n");
    int n1 = 6;
    GrafoLista *dag = criar_grafo(n1);

    adicionar_aresta_dirigida(dag, 5, 2);
    adicionar_aresta_dirigida(dag, 5, 0);
    adicionar_aresta_dirigida(dag, 4, 0);
    adicionar_aresta_dirigida(dag, 4, 1);
    adicionar_aresta_dirigida(dag, 2, 3);
    adicionar_aresta_dirigida(dag, 3, 1);

    printf("E DAG? %s\n", eh_dag(dag) ? "Sim" : "Nao");

    int t1_kahn = 0, t1_dfs = 0;
    int *ordem_kahn = ordenacao_topologica_kahn(dag, &t1_kahn);
    int *ordem_dfs = ordenacao_topologica_dfs(dag, &t1_dfs);

    imprimir_ordem("Ordem Topologica (Kahn)", ordem_kahn, t1_kahn);
    imprimir_ordem("Ordem Topologica (DFS) ", ordem_dfs, t1_dfs);

    free(ordem_kahn);
    free(ordem_dfs);
    destruir_grafo(dag);

    printf("\n=== Teste 2: Grafo Com Ciclo ===\n");
    int n2 = 3;
    GrafoLista *ciclico = criar_grafo(n2);


    adicionar_aresta_dirigida(ciclico, 0, 1);
    adicionar_aresta_dirigida(ciclico, 1, 2);
    adicionar_aresta_dirigida(ciclico, 2, 0);

    printf("E DAG? %s\n", eh_dag(ciclico) ? "Sim" : "Nao");

    int t2_kahn = 0;
    int *ordem_cica = ordenacao_topologica_kahn(ciclico, &t2_kahn);
    imprimir_ordem("Ordem Topologica (Kahn)", ordem_cica, t2_kahn);

    destruir_grafo(ciclico);

    return 0;
}