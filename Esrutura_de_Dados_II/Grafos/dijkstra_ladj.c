#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int vertex;
    int w;
    struct Node* next;
}Node;

typedef struct grafo {
    int v;
    Node** listas;
}Grafo;

typedef struct {
    int dist;
    int v;
}HeapNode;

typedef struct {
    HeapNode** arr;
    int size;
    int max;
}MinHeap;

Grafo* criarGrafo(int v);
Node* criarNode(int v, int w);
void adicionarAresta(Grafo* g, int d, int s, int w);
void mostrarArvore(Grafo* g);
void limparGrafo(Grafo* g);
void dijkstra(Grafo* g, int s, int* pre, int* dist);
int relaxarAresta(int u, int v, int w, int dist[], int pre[], MinHeap* heap);
MinHeap* criarHeap(int max);
void swap(HeapNode** a, HeapNode** b);
void inserirHeap(MinHeap* heap, int dist, int v);
HeapNode* extrairHeap(MinHeap* heap);
void limparHeap(MinHeap* heap);

int main(void) {
    int vertices = 5;
    Grafo* g = criarGrafo(vertices);

    adicionarAresta(g, 1, 0, 1); // 0->1 peso 1
    adicionarAresta(g, 0, 1, 1); // 1->0 peso 1
    adicionarAresta(g, 2, 1, 2); // 1->2 peso 2
    adicionarAresta(g, 1, 2, 2); // 2->1 peso 2
    adicionarAresta(g, 4, 2, 1); // 2->4 peso 1
    adicionarAresta(g, 2, 4, 1); // 4->2 peso 1
    adicionarAresta(g, 4, 3, 3); // 3->4 peso 3
    adicionarAresta(g, 3, 4, 3); // 4->3 peso 3
    adicionarAresta(g, 3, 0, 4); // 0->3 peso 4
    adicionarAresta(g, 0, 3, 4); // 3->0 peso 4

    printf("=== Estrutura do grafo ===\n");
    mostrarArvore(g);

    int dist[vertices];
    int pre[vertices];
    int origem = 0;

    printf("\n=== Dijkstra a partir do vertice %d ===\n", origem);
    dijkstra(g, origem, pre, dist);

    for (int i = 0; i < vertices; i++) {
        if (dist[i] == INT_MAX)
            printf("Vertice %d: inalcancavel\n", i);
        else
            printf("Vertice %d: distancia = %d | predecessor = %d\n", i, dist[i], pre[i]);
    }

    // Reconstruir caminho até vértice 4
    printf("\n=== Caminho de %d ate 4 ===\n", origem);
    int caminho[vertices];
    int tam = 0;
    int atual = 4;

    while (atual != -1) {
        caminho[tam++] = atual;
        atual = pre[atual];
    }

    for (int i = tam - 1; i >= 0; i--) {
        if (i > 0) printf("%d -> ", caminho[i]);
        else printf("%d\n", caminho[i]);
    }

    limparGrafo(g);
    return 0;
}

Grafo* criarGrafo(int v) {
    Grafo* g = malloc(sizeof(Grafo));
    if (!g) {
        printf("erro ao alocar memoria");
        return NULL;
    }

    g->v=v;

    g->listas = calloc(v, sizeof(Node*));
    if (!g->listas) {
        return NULL;
    }

    return g;
}

Node* criarNode(int v, int w) {
    Node* n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->vertex = v;
    n->w = w;
    n->next = NULL;

    return n;
}

void adicionarAresta(Grafo* g, int d, int s, int w) {
    if (!g) return;
    Node* newNode = criarNode(d, w);
    newNode->next = g->listas[s];
    g->listas[s] = newNode;
}

void mostrarArvore(Grafo* g) {
    if (!g) return;

    for (int i = 0; i<g->v; i++) {
        Node* temp = g->listas[i];
        printf("Vertide %d", i);
        while (temp) {
            printf(" - %d -> %d", temp->w, temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void limparGrafo(Grafo* g) {
    if (!g) return;

    for (int i = 0; i<g->v; i++) {
        Node* temp = g->listas[i];
        while (temp) {
            g->listas[i] = temp->next;
            free(temp);
            temp = g->listas[i];
        }
    }
    free(g->listas);
    free(g);
}

void dijkstra(Grafo* g, int s, int* pre, int* dist) {
    int visit[g->v];

    for (int i=0; i < g->v; i++) {
        dist[i] = INT_MAX;
        pre[i] = -1;
        visit[i] = 0;
    }

    dist[s] = 0;

    MinHeap* heap = criarHeap(g->v);
    inserirHeap(heap, 0, s);

    while (heap->size) {
        HeapNode* nx = extrairHeap(heap);
        if (!nx) break;
        int u = nx->v;
        free(nx);
        if (visit[u]) continue;

        visit[u] = 1;

        Node* vizinho = g->listas[u];

        while (vizinho!=NULL) {
            int v = vizinho->vertex;
            int vw = vizinho->w;
            if (!visit[v])
                relaxarAresta(u, v, vw, dist, pre, heap);
            vizinho = vizinho->next;
        }
    }

    limparHeap(heap);
}

MinHeap* criarHeap(int max) {
    MinHeap* h = malloc(sizeof(MinHeap));
    if (!h) return NULL;
    h->max = max;
    h->size = 0;
    h->arr = malloc(sizeof(HeapNode*)*h->max);
    if (!h->arr) {
        free(h);
        return NULL;
    }

    return h;
}

int relaxarAresta(int u, int v, int w, int dist[], int pre[], MinHeap* heap) {
    int nova_distancia = dist[u] + w;

    if (nova_distancia < dist[v]) {
        //achamos um caminho menor, aresta estava tensa
        dist[v] = nova_distancia;
        pre[v] = u;

        inserirHeap(heap, nova_distancia, v);
        return 1;
    }
    return 0;
}

void swap(HeapNode** a, HeapNode** b) {
    HeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void inserirHeap(MinHeap* heap, int dist, int v) {
    int i = heap->size;
    heap->size++;

    heap->arr[i] = malloc(sizeof(HeapNode));
    heap->arr[i]->dist = dist;
    heap->arr[i]->v = v;

    while (i!=0 && heap->arr[(i-1)/2]->dist > heap->arr[i]->dist) {
        swap(&heap->arr[i], &heap->arr[(i-1)/2]);
        i=(i-1)/2;
    }
}

HeapNode* extrairHeap(MinHeap* heap) {
    if (!heap || heap->size == 0) return NULL;

    HeapNode* root = heap->arr[0];

    heap->size--;
    heap->arr[0] = heap->arr[heap->size];

    int i = 0;
    while (1) {
        int left = (2*i) + 1;
        int right = (2*i) + 2;
        int min = i;

        if (left < heap->size && heap->arr[left]->dist < heap->arr[min]->dist)
            min = left;

        if (right < heap->size && heap->arr[right]->dist < heap->arr[min]->dist)
            min = right;

        if (min != i) {
            swap(&heap->arr[i], &heap->arr[min]);
            i = min;
        }else {
            break;
        }
    }
    return root;
}

void limparHeap(MinHeap* heap) {
    if (!heap) return;

    for (int i = 0; i<heap->size; i++)
        if (heap->arr!=NULL) free(heap->arr[i]);
    free(heap->arr);
    free(heap);
}