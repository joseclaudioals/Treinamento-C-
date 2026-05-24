#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
}Node;

typedef struct grafo {
    int v;
    Node** listas;
}Grafo;

Grafo* criarGrafo(int v);
Node* criarNode(int v);
void adicionarAresta(Grafo* g, int s, int d);
void limparGrafo(Grafo* g);
void mostrarGrafo(const Grafo* g);

int main(void) {
    Grafo* g = criarGrafo(5);

    adicionarAresta(g, 0, 2);
    adicionarAresta(g, 0, 1);
    adicionarAresta(g, 0, 3);
    adicionarAresta(g, 1, 2);

    mostrarGrafo(g);
    limparGrafo(g);

    return 0;
}

Grafo* criarGrafo(int v) {
    Grafo* g = malloc(sizeof(Grafo));
        if (!g) {
            printf("Erro ao alocar memoria para o grafo\n");
            return NULL;
        }

    g->v = v;

    g->listas = malloc(sizeof(Node)*v);
    if (!g->listas) {
        printf("Erro ao alocar memoria para listas\n");
        return NULL;
    }

    for (int i = 0; i<g->v; i++) {
        g->listas[i] = NULL;
    }

    return g;
}

Node* criarNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void adicionarAresta(Grafo* g, int s, int d) {
    if (!g) {
        printf("Grafo está vazio\n");
        return;
    }
    Node* newNode = criarNode(d);
    newNode->next = g->listas[s];
    g->listas[s] = newNode;

    /* se o grafo for dirigido retire os comentarios comente as proximas linhas */

    newNode = criarNode(s);
    newNode->next = g->listas[d];
    g->listas[d] = newNode;

}

void limparGrafo(Grafo* g) {
    if (!g) {
        printf("o grafo esta vazio\n");
        return;
    }
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

void mostrarGrafo(const Grafo* g) {
    for (int i = 0; i < g->v; i++) {
        Node* temp = g->listas[i];
        printf("Vertice %d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
