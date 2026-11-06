#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cobertura.h"

int main() {
    srand(42); 

    int valores_n[] = {5, 8, 10, 12, 15};
    int total_testes = sizeof(valores_n) / sizeof(valores_n[0]);

    printf("======================================================================\n");
    printf(" EXPERIMENTO: COBERTURA DE VERTICES (BACKTRACKING vs HEURISTICA GULOSA)\n");
    printf("======================================================================\n\n");
    printf("%-5s | %-12s | %-14s | %-12s | %-14s\n", 
           "n", "Tam BT", "Tempo BT (s)", "Tam Gulosa", "Tempo Gul. (s)");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < total_testes; i++) {
        int n = valores_n[i];
        Grafo* g = gerar_grafo_aleatorio(n, 0.5); 

        bool sol_bt[MAX_V] = {false};
        bool sol_gulosa[MAX_V] = {false};

        
        clock_t inicio = clock();
        int tam_bt = cobertura_minima_bt(g, sol_bt);
        clock_t fim = clock();
        double tempo_bt = (double)(fim - inicio) / CLOCKS_PER_SEC;

        
        inicio = clock();
        int tam_gulosa = cobertura_gulosa(g, sol_gulosa);
        fim = clock();
        double tempo_gulosa = (double)(fim - inicio) / CLOCKS_PER_SEC;

        printf("%-5d | %-12d | %-14.6f | %-12d | %-14.6f\n", 
               n, tam_bt, tempo_bt, tam_gulosa, tempo_gulosa);

        liberar_grafo(g);
    }

    printf("----------------------------------------------------------------------\n");
    return 0;
}