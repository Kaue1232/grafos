#include "coloracao.h"

GrafoLista* criar_grafo(int vertices) {
    GrafoLista* g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = vertices;
    g->listas = (No**) malloc(vertices * sizeof(No*));
    for (int i = 0; i < vertices; i++) {
        g->listas[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista* g, int u, int v) {
    // Grafo não-direcionado
    No* novo1 = (No*) malloc(sizeof(No));
    novo1->vertice = v;
    novo1->proximo = g->listas[u];
    g->listas[u] = novo1;

    No* novo2 = (No*) malloc(sizeof(No));
    novo2->vertice = u;
    novo2->proximo = g->listas[v];
    g->listas[v] = novo2;
}

void liberar_grafo(GrafoLista* g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No* atual = g->listas[i];
        while (atual) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->listas);
    free(g);
}

// 1. Coloração Gulosa (Ordenação arbitrária de 0 a V-1)
int* coloracao_gulosa(GrafoLista *g, int *num_cores) {
    int V = g->num_vertices;
    int* cor = (int*) malloc(V * sizeof(int));
    bool* disponivel = (bool*) malloc(V * sizeof(bool));

    for (int i = 0; i < V; i++) {
        cor[i] = -1;
        disponivel[i] = true;
    }

    // Atribui a primeira cor (0) ao primeiro vértice
    cor[0] = 0;
    int max_cor = 0;

    for (int u = 1; u < V; u++) {
        // Marca cores dos vizinhos já coloridos como indisponíveis
        for (No* p = g->listas[u]; p != NULL; p = p->proximo) {
            int vizinho = p->vertice;
            if (cor[vizinho] != -1) {
                disponivel[cor[vizinho]] = false;
            }
        }

        // Encontra a menor cor disponível
        int cr;
        for (cr = 0; cr < V; cr++) {
            if (disponivel[cr]) break;
        }

        cor[u] = cr;
        if (cr > max_cor) max_cor = cr;

        // Reseta o vetor de disponibilidade
        for (No* p = g->listas[u]; p != NULL; p = p->proximo) {
            int vizinho = p->vertice;
            if (cor[vizinho] != -1) {
                disponivel[cor[vizinho]] = true;
            }
        }
    }

    *num_cores = max_cor + 1;
    free(disponivel);
    return cor;
}

// Estrutura auxiliar para ordenação dos vértices por grau
typedef struct {
    int vertice;
    int grau;
} VerticeGrau;

int comparar_grau(const void* a, const void* b) {
    VerticeGrau* v1 = (VerticeGrau*) a;
    VerticeGrau* v2 = (VerticeGrau*) b;
    return v2->grau - v1->grau; // Decrescente
}

// 2. Coloração Welsh-Powell (Ordenação por grau decrescente)
int* coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    int V = g->num_vertices;
    VerticeGrau* vg = (VerticeGrau*) malloc(V * sizeof(VerticeGrau));

    for (int i = 0; i < V; i++) {
        vg[i].vertice = i;
        vg[i].grau = 0;
        for (No* p = g->listas[i]; p != NULL; p = p->proximo) {
            vg[i].grau++;
        }
    }

    // Ordena vértices por grau decrescente
    qsort(vg, V, sizeof(VerticeGrau), comparar_grau);

    int* cor = (int*) malloc(V * sizeof(int));
    bool* disponivel = (bool*) malloc(V * sizeof(bool));

    for (int i = 0; i < V; i++) {
        cor[i] = -1;
        disponivel[i] = true;
    }

    int max_cor = 0;

    for (int i = 0; i < V; i++) {
        int u = vg[i].vertice;

        for (No* p = g->listas[u]; p != NULL; p = p->proximo) {
            int vizinho = p->vertice;
            if (cor[vizinho] != -1) {
                disponivel[cor[vizinho]] = false;
            }
        }

        int cr;
        for (cr = 0; cr < V; cr++) {
            if (disponivel[cr]) break;
        }

        cor[u] = cr;
        if (cr > max_cor) max_cor = cr;

        for (No* p = g->listas[u]; p != NULL; p = p->proximo) {
            int vizinho = p->vertice;
            if (cor[vizinho] != -1) {
                disponivel[cor[vizinho]] = true;
            }
        }
    }

    *num_cores = max_cor + 1;
    free(vg);
    free(disponivel);
    return cor;
}

// 3. Verificação de Grafo Bipartido (2-coloração via BFS)
bool eh_bipartido(GrafoLista *g) {
    int V = g->num_vertices;
    int* cor = (int*) malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) cor[i] = -1;

    int* fila = (int*) malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        if (cor[i] == -1) {
            cor[i] = 1;
            int inicio = 0, fim = 0;
            fila[fim++] = i;

            while (inicio < fim) {
                int u = fila[inicio++];

                for (No* p = g->listas[u]; p != NULL; p = p->proximo) {
                    int v = p->vertice;

                    if (cor[v] == -1) {
                        cor[v] = 1 - cor[u];
                        fila[fim++] = v;
                    } else if (cor[v] == cor[u]) {
                        free(cor);
                        free(fila);
                        return false;
                    }
                }
            }
        }
    }

    free(cor);
    free(fila);
    return true;
}