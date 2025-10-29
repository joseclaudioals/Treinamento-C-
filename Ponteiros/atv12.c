#include <stdio.h>

void copiaArr(int* origem, int* destino, int tamanho){
    for(int i=0; i<tamanho; i++){
        *destino = *origem;
        destino++, origem++;
    }
}

int main(void){
    int arr1[]={1, 2, 3, 4, 5};
    int size = sizeof(arr1)/sizeof(arr1[0]);
    int arrDest[size];

    printf("array origem: ");
    for(int i=0; i<size; i++)
        printf("%i ", arr1[i]);
    printf("\n");

    copiaArr(arr1, arrDest, size);

    printf("array inicial: ");
    for(int i=0; i<size; i++)
        printf("%i ", arrDest[i]);
    printf("\n");

    return 0;
}