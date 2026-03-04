#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int valor;
    struct node* esquerda;
    struct node* direita;
}Node;

void inserirDinamico(Node** raiz, int inicio, int fim, int* arr){
    if(inicio>fim)
        return;

    int meio = (inicio+fim)/2;

    *raiz = malloc(sizeof(**raiz));

    (*raiz)->valor = arr[meio];
    (*raiz)->esquerda=NULL;
    (*raiz)->direita=NULL;

    inserirDinamico(&(*raiz)->esquerda, inicio, meio-1, arr);
    inserirDinamico(&(*raiz)->direita, meio+1, fim, arr);
}

void printarArvore(Node* raiz, int margem) {
    if (raiz==NULL) return;

    int distancia = 5;
    margem+=distancia;

    printarArvore(raiz->direita, margem);

    printf("\n");
    for (int i=distancia; i<margem; i++)
        printf(" ");

    printf("%d\n", raiz->valor);

    printarArvore(raiz->esquerda, margem);
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Node* raiz = NULL;

    inserirDinamico(&raiz, 0, sizeof(arr)/sizeof(int)-1, arr);
    printarArvore(raiz, 0);

    return 0;
}