/*Escreva uma função que busca por um valor específico em um array de inteiros. A função deve retornar um ponteiro para a primeira ocorrência do valor no array. Se o valor não for encontrado, a função deve retornar NULL.*/

#include <stdio.h>

int* buscarN(int *arr, int tamanho, int valorBuscado, int* posicao);

int main(void){
    int arr[9]={1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n, posicao;
    int* nBusca;

    printf("array:\n");
    for(unsigned int i=0; i < (sizeof(arr)/sizeof(arr[0])); i++){
        printf("%i ", arr[i]);
    }

    printf("\ninsira um valor para ser buscado no array:");
    scanf(" %i", &n);

    nBusca = buscarN(arr, sizeof(arr)/sizeof(arr[0]), n, &posicao);

    if(nBusca)
        printf("o numero foi achado\nvalor = %i\nindice do valor = %i\n", *nBusca, posicao);
        else
            printf("o valor %i nao esta no array dado\n", n);
}

int* buscarN(int* arr, int tamanho, int valorBuscado, int* posicao){
    for(int i = 0; i<tamanho; i++){
        if(*arr==valorBuscado){
            *posicao=i;
            return arr;
        }
        arr++;
    }

    return NULL;
}
