#include <stdio.h>
void insertionSort(int arr[], int size);

int main(void){
    int arr[]={4,2,5,1,3};
    int size = sizeof(arr)/sizeof(int);
    printf("array unsorted: ");
    for(int i=0; i<size; i++){
        printf("%i ", arr[i]);
    }
    printf("\n");

    insertionSort(arr, size);

    printf("array sorted: ");
    for(int i=0; i<size; i++){
        printf("%i ", arr[i]);
    }
    printf("\n");

    return 0;
}

void insertionSort(int arr[], int size){
    for(int i=1; i<size; i++){
        int key = arr[i]; // armazena o valor do elemento chave a ser comparado
        int j = i-1; // armazena o indice anterior ao da chave
        //o loop irá rodar enquanto o valor de chave for menor que o valor a esquerda for maior que ele 
        //o loop tambem verifica j>=0 para nao sair dos limites do array
        while(key<arr[j] && j>=0){
            arr[j+1]=arr[j]; 
            //se o valor de j for maior que a chave, deslocamos ele para a direita
            j-=1;
            //diminuimos o valor de j para verificar os outros elementos a esquerda 
        }
        arr[j+1]=key;
        //somamos j+1 por que j sempre ao sair do while
        //estará um indice atrás da posição correta 
        printf("array at moment: ");
        for(int i=0; i<size; i++){
            printf("%i ", arr[i]);
        }
        printf("\n");
    }
}
