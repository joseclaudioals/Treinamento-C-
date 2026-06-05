#include <stdio.h>
#include <limits.h>

#define V 5

void iniciarGrafo(int g[][V]);
void addAresta(int g[][V], int s, int d, int w);
void dijkstra(int g[][V], int s);

int main(void) {
    int g[V][V];
    iniciarGrafo(g);

    addAresta(g, 0, 1, 1);
    addAresta(g, 1, 2, 2);
    addAresta(g, 2, 4, 1);
    addAresta(g, 0, 3, 4);
    addAresta(g, 3, 4, 3);

    dijkstra(g, 0);

    return 0;
}

void iniciarGrafo(int g[][V]) {
    for (int i = 0; i<V; i++)
        for (int j = 0; j<V; j++)
            g[i][j] = 0;
}

void addAresta(int g[][V], int s, int d, int w) {
    g[s][d] = w;
}

void dijkstra(int g[][V], int s) {
    int dist[V], pre[V], visit[V];

    for (int i=0; i<V; i++) {
        dist[i] = INT_MAX;
        pre[i] = -1;
        visit[i] = 0;
    }

    dist[s] = 0;

    for (int count = 0; count < V-1; count++) {
        int min = INT_MAX;
        int u = -1;
        for (int i = 0; i<V; i++) {
            if (dist[i] < min && !visit[i]) {
                min = dist[i];
                u = i;
            }
        }
        //se todos os vertices forem inalcançáveis u será -1
        if (u == -1) break;
        visit[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visit[v] && g[u][v]!=0)
                if (dist[u] != INT_MAX && dist[u] + g[u][v] < dist[v]) {
                    dist[v] = dist[u] + g[u][v];
                    pre[v] = u;
            }
        }
    }
    printf("\n -- Resultados --\nOrigem: %d\n", s);
    printf("Vertice \t Distancia \t Predecessor\n");
    for (int i = 0; i<V; i++) {
        if (dist[i] == INT_MAX)
            printf("%d \t\t Inalcancavel \t -\n", i);
        else
            printf("%d \t\t %d \t\t %d\n", i, dist[i], pre[i]);
    }
}

