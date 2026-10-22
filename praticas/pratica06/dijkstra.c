#include "dijkstra.h"

// Funções Auxiliares do Heap
static void trocar_nos(MinHeap* heap, int i, int j) {
    heap->posicao[heap->dados[i].vertice] = j;
    heap->posicao[heap->dados[j].vertice] = i;
    NoHeap temp = heap->dados[i];
    heap->dados[i] = heap->dados[j];
    heap->dados[j] = temp;
}

static void refazer_heap(MinHeap* heap, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < heap->tamanho && heap->dados[esq].distancia < heap->dados[menor].distancia)
        menor = esq;
    if (dir < heap->tamanho && heap->dados[dir].distancia < heap->dados[menor].distancia)
        menor = dir;

    if (menor != idx) {
        trocar_nos(heap, idx, menor);
        refazer_heap(heap, menor);
    }
}

// Funções Solicitadas do MinHeap
MinHeap* criar_min_heap(int capacidade) {
    MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->capacidade = capacidade;
    heap->tamanho = 0;
    heap->dados = (NoHeap*) malloc(capacidade * sizeof(NoHeap));
    heap->posicao = (int*) malloc(capacidade * sizeof(int));
    for (int i = 0; i < capacidade; i++) {
        heap->posicao[i] = -1;
    }
    return heap;
}

void liberar_min_heap(MinHeap* heap) {
    free(heap->dados);
    free(heap->posicao);
    free(heap);
}

NoHeap extrair_minimo(MinHeap* heap) {
    NoHeap raiz = heap->dados[0];
    NoHeap ultimo = heap->dados[heap->tamanho - 1];
    
    heap->dados[0] = ultimo;
    heap->posicao[raiz.vertice] = -1;
    heap->posicao[ultimo.vertice] = 0;
    
    heap->tamanho--;
    refazer_heap(heap, 0);
    
    return raiz;
}

void diminuir_chave(MinHeap* heap, int vertice, int nova_distancia) {
    int i = heap->posicao[vertice];
    
    // Se o vértice ainda não estiver no heap, inserimos ele
    if (i == -1) {
        i = heap->tamanho;
        heap->tamanho++;
    }
    
    heap->dados[i].vertice = vertice;
    heap->dados[i].distancia = nova_distancia;
    heap->posicao[vertice] = i;

    // Subir nó mantendo propriedade do Min-Heap
    while (i > 0 && heap->dados[i].distancia < heap->dados[(i - 1) / 2].distancia) {
        trocar_nos(heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// Grafo e Dijkstra
GrafoListaPonderado* criar_grafo(int num_vertices) {
    GrafoListaPonderado* g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->listas = (No**) malloc(num_vertices * sizeof(No*));
    for (int i = 0; i < num_vertices; i++) {
        g->listas[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoListaPonderado* g, int u, int v, int peso) {
    No* novo = (No*) malloc(sizeof(No));
    novo->destino = v;
    novo->peso = peso;
    novo->proximo = g->listas[u];
    g->listas[u] = novo;
}

void liberar_grafo(GrafoListaPonderado* g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No* atual = g->listas[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->listas);
    free(g);
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int V = g->num_vertices;
    MinHeap* heap = criar_min_heap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INF;
        pred[v] = -1;
    }

    dist[origem] = 0;
    diminuir_chave(heap, origem, 0);

    while (heap->tamanho > 0) {
        NoHeap min_no = extrair_minimo(heap);
        int u = min_no.vertice;

        No* adj = g->listas[u];
        while (adj != NULL) {
            int v = adj->destino;
            int peso = adj->peso;

            if (dist[u] != INF && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pred[v] = u;
                diminuir_chave(heap, v, dist[v]);
            }
            adj = adj->proximo;
        }
    }
    liberar_min_heap(heap);
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    if (origem == destino) {
        printf("%d", origem);
        return;
    }
    if (pred[destino] == -1) {
        printf("Não há caminho entre %d e %d\n", origem, destino);
        return;
    }
    reconstruir_caminho(origem, pred[destino], pred);
    printf(" -> %d", destino);
}