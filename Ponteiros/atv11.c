#include <stdio.h>

void reverseArr(int* arr, int tamanho){
    int *inicio = arr;
    int *fim = arr+tamanho-1;

    for(int i = 0; i<tamanho/2; i++){
        int temp = *inicio;
        *inicio = *fim;
        *fim = temp;

        inicio++;
        fim--;
    }
}

int main(void){
    int arr[]={1, 2, 3, 4};
    int size = sizeof(arr)/sizeof(arr[0]);

    printf("array inicial: ");
    for(int i=0; i<size; i++)
        printf("%i ", arr[i]);
    printf("\n");

    reverseArr(arr, size);

    printf("array final: ");
    for(int i=0; i<size; i++)
        printf("%i ", arr[i]);
    printf("\n");

    return 0;
}