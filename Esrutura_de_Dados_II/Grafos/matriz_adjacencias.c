#include <stdio.h>
#define V 4

void iniciarGrafo(int adj[][V]){
    for (int i=0; i<V; i++) {
        for (int j=0; j<V; j++)
            adj[i][j] = 0;
    }
}

void adicionarAresta(int adj[][V], int s, int d){
    adj[s][d] = 1;
    adj[d][s] = 1;
}

void mostrarGrafo(int adj[][V]) {
    for (int i = 0; i<V; i++) {
        printf("Vertice %d: ", i);
        for (int j = 0; j<V; j++) {
            if (adj[i][j]) printf("-> %d", j);
        }
        printf("\n");
    }
}

int main(void) {
    int adj[V][V];
    iniciarGrafo(adj);

    adicionarAresta(adj, 0, 1);
    adicionarAresta(adj, 0, 2);
    adicionarAresta(adj, 1, 2);
    adicionarAresta(adj, 2, 0);
    adicionarAresta(adj, 2, 3);

    mostrarGrafo(adj);

    return 0;
}