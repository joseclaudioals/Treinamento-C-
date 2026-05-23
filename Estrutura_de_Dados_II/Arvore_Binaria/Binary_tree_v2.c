#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    struct Node* esquerda;
    struct Node* direita;
}Node;

Node* construirArvore(const int* arr, int inicio, int fim) {
    if (inicio>fim) {
        return NULL;
    }
    Node* raiz = malloc(sizeof(Node));

    int meio = (inicio+fim)/2;

    raiz->valor=arr[meio];
    raiz->direita=construirArvore(arr, meio+1, fim);
    raiz->esquerda=construirArvore(arr, inicio, meio-1);

    return raiz;
}

void printarArvore(const Node* raiz, int margem) {
    if (raiz!=NULL) {
        printarArvore(raiz->esquerda, margem+5);
        printf("%*s %d\n", margem," ", raiz->valor);
        printarArvore(raiz->direita, margem+5);
    }
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    Node* raiz = construirArvore(arr, 0, sizeof(arr)/sizeof(int)-1);
    printarArvore(raiz, 5);

    return 0;
}