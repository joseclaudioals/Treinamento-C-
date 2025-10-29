/*Crie uma função zerar_array que recebe um ponteiro para o primeiro elemento de um array de inteiros e o tamanho do array. A função deve percorrer o array, usando apenas aritmética de ponteiros, e atribuir o valor 0 a cada um de seus elementos.*/

#include <stdio.h>

void zerarArray(int* p, int tamanho){
    for(int i=0; i < tamanho - 1; i++){
        *p = 0;
        p++;
    }
}

int main(void){
    int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("array inicial:\n");
    for(unsigned int i=0; i < (sizeof(arr)/sizeof(arr[0])); i++){
        printf("%i ", arr[i]);
    }

    zerarArray(arr, (sizeof(arr)/sizeof(arr[0])));

    printf("\narray final:\n");
    for(unsigned int i=0; i < (sizeof(arr)/sizeof(arr[0])); i++){
        printf("%i ", arr[i]);
    }

    return 0;

}