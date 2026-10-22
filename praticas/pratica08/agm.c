#include "agm.h"

// --- DSU (Union-Find) ---
DSU* criarDSU(int n) {
    DSU *d = (DSU*) malloc(sizeof(DSU));
    d->n = n;
    d->pai = (int*) malloc(n * sizeof(int));
    d->rank = (int*) calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) d->pai[i] = i;
    return d;
}

void destruirDSU(DSU *d) {
    free(d->pai);
    free(d->rank);
    free(d);
}

// Find com compressão de caminho
int find(DSU *d, int x) {
    if (d->pai[x] != x)
        d->pai[x] = find(d, d->pai[x]);
    return d->pai[x];
}

// Unir com união por rank
bool unir(DSU *d, int x, int y) {
    int rx = find(d, x);
    int ry = find(d, y);
    if (rx == ry) return false;

    if (d->rank[rx] < d->rank[ry]) {
        d->pai[rx] = ry;
    } else if (d->rank[rx] > d->rank[ry]) {
        d->pai[ry] = rx;
    } else {
        d->pai[ry] = rx;
        d->rank[rx]++;
    }
    return true;
}

// Comparador para qsort
static int compararArestas(const void *a, const void *b) {
    return ((Aresta*)a)->peso - ((Aresta*)b)->peso;
}

// Algoritmo de Kruskal: O(E log E)
int kruskal(int V, Aresta *arestas, int E) {
    qsort(arestas, E, sizeof(Aresta), compararArestas);
    DSU *d = criarDSU(V);
    int pesoTotal = 0, arestasUsadas = 0;

    for (int i = 0; i < E; i++) {
        if (unir(d, arestas[i].u, arestas[i].v)) {
            pesoTotal += arestas[i].peso;
            if (++arestasUsadas == V - 1) break;
        }
    }

    destruirDSU(d);
    return pesoTotal;
}

// --- Grafo & Min-Heap Otimizado para Prim ---
Grafo* criarGrafo(int V) {
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    g->V = V;
    g->cabecas = (NoAdj**) calloc(V, sizeof(NoAdj*));
    return g;
}

void adicionarAresta(Grafo* g, int u, int v, int peso) {
    NoAdj* novo = (NoAdj*) malloc(sizeof(NoAdj));
    novo->v = v; novo->peso = peso; novo->prox = g->cabecas[u];
    g->cabecas[u] = novo;

    novo = (NoAdj*) malloc(sizeof(NoAdj));
    novo->v = u; novo->peso = peso; novo->prox = g->cabecas[v];
    g->cabecas[v] = novo;
}

void destruirGrafo(Grafo* g) {
    for (int i = 0; i < g->V; i++) {
        NoAdj* atual = g->cabecas[i];
        while (atual) {
            NoAdj* tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }
    free(g->cabecas);
    free(g);
}

static void trocarHeap(MinHeap *h, int i, int j) {
    ElementoHeap temp = h->array[i];
    h->array[i] = h->array[j];
    h->array[j] = temp;
    h->pos[h->array[i].v] = i;
    h->pos[h->array[j].v] = j;
}

static void minHeapify(MinHeap *h, int idx) {
    int menor = idx, esq = 2 * idx + 1, dir = 2 * idx + 2;
    if (esq < h->tamanho && h->array[esq].chave < h->array[menor].chave) menor = esq;
    if (dir < h->tamanho && h->array[dir].chave < h->array[menor].chave) menor = dir;

    if (menor != idx) {
        trocarHeap(h, idx, menor);
        minHeapify(h, menor);
    }
}

static ElementoHeap extrairMin(MinHeap *h) {
    ElementoHeap min = h->array[0];
    ElementoHeap ultimo = h->array[--h->tamanho];
    h->array[0] = ultimo;
    h->pos[min.v] = -1;
    h->pos[ultimo.v] = 0;
    minHeapify(h, 0);
    return min;
}

static void diminuirChave(MinHeap *h, int v, int chave) {
    int i = h->pos[v];
    h->array[i].chave = chave;
    while (i && h->array[i].chave < h->array[(i - 1) / 2].chave) {
        trocarHeap(h, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// Algoritmo de Prim: O((V + E) log V)
int prim(Grafo* g, int origem) {
    int V = g->V;
    int *chave = (int*) malloc(V * sizeof(int));
    bool *noHeap = (bool*) malloc(V * sizeof(bool));

    MinHeap h;
    h.capacidade = V;
    h.tamanho = V;
    h.pos = (int*) malloc(V * sizeof(int));
    h.array = (ElementoHeap*) malloc(V * sizeof(ElementoHeap));

    for (int i = 0; i < V; i++) {
        chave[i] = INT_MAX;
        h.array[i] = (ElementoHeap){i, chave[i]};
        h.pos[i] = i;
        noHeap[i] = true;
    }

    chave[origem] = 0;
    diminuirChave(&h, origem, 0);

    int pesoTotal = 0;

    while (h.tamanho > 0) {
        ElementoHeap min = extrairMin(&h);
        int u = min.v;
        noHeap[u] = false;
        pesoTotal += min.chave;

        for (NoAdj* p = g->cabecas[u]; p != NULL; p = p->prox) {
            int v = p->v;
            if (noHeap[v] && p->peso < chave[v]) {
                chave[v] = p->peso;
                diminuirChave(&h, v, chave[v]);
            }
        }
    }

    free(chave); free(noHeap); free(h.pos); free(h.array);
    return pesoTotal;
}