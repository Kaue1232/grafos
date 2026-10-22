#include "agm.h"

int main() {
    int V = 5, E = 7;
    Aresta arestas[] = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3},
        {1, 3, 8}, {1, 4, 5}, {2, 4, 7}, {3, 4, 9}
    };

    // Teste do Kruskal
    int pesoKruskal = kruskal(V, arestas, E);
    printf("Peso minimo (Kruskal): %d\n", pesoKruskal);

    // Teste do Prim
    Grafo* g = criarGrafo(V);
    for (int i = 0; i < E; i++) {
        adicionarAresta(g, arestas[i].u, arestas[i].v, arestas[i].peso);
    }
    int pesoPrim = prim(g, 0);
    printf("Peso minimo (Prim): %d\n", pesoPrim);

    destruirGrafo(g);
    return 0;
}