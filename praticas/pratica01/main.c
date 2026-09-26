#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main() {
    int n = 5;

    // Teste com Matriz de Adjacência
    GrafoMatriz *gm = criar_grafo_matriz(n);
    inserir_aresta_matriz(gm, 0, 1);
    inserir_aresta_matriz(gm, 0, 4);
    inserir_aresta_matriz(gm, 1, 2);

    printf("--- Teste Matriz ---\n");
    printf("0 e 1 adjacentes? %s\n", sao_adjacentes_matriz(gm, 0, 1) ? "Sim" : "Nao");
    printf("Grau do vertice 0: %d\n", grau_matriz(gm, 0));

    remover_aresta_matriz(gm, 0, 1);
    printf("Apos remover (0,1), sao adjacentes? %s\n", sao_adjacentes_matriz(gm, 0, 1) ? "Sim" : "Nao");
    liberar_grafo_matriz(gm);

    // Teste com Lista de Adjacência
    GrafoLista *gl = criar_grafo_lista(n);
    inserir_aresta_lista(gl, 0, 1);
    inserir_aresta_lista(gl, 0, 4);
    inserir_aresta_lista(gl, 1, 2);

    printf("\n--- Teste Lista ---\n");
    printf("0 e 1 adjacentes? %s\n", sao_adjacentes_lista(gl, 0, 1) ? "Sim" : "Nao");
    printf("Grau do vertice 0: %d\n", grau_lista(gl, 0));

    remover_aresta_lista(gl, 0, 1);
    printf("Apos remover (0,1), sao adjacentes? %s\n", sao_adjacentes_lista(gl, 0, 1) ? "Sim" : "Nao");
    liberar_grafo_lista(gl);

    return 0;
}