/*
    Crie uma função chamada aplicar_funcao_array. Ela deve receber um array de double, seu tamanho e um ponteiro para uma função que recebe um double e retorna um double. A função aplicar_funcao_array deve aplicar a função recebida a cada elemento do array, modificando-o.
*/

#include <stdio.h>

void aplicandoFuncao(double *arr, int tamanho, double (*func)(double)){
    for(int i=0; i<tamanho; i++){
        arr[i] = func(arr[i]);
    }
}
void imprimir(const char* titulo, double *arr, int tamanho){
    printf("%s", titulo);
    for(int i= 0; i < tamanho; i++){
        printf(" %.2f ", arr[i]);
    }
    printf("\n");
}
double dobro(double n){
    return n*2;
}
double metade(double n){
    return n/2;
}

int main(void){
    double arr[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
    unsigned int tamanho = sizeof(arr)/sizeof(arr[0]);

    aplicandoFuncao(arr, tamanho, metade);
    imprimir("Array pela metade", arr, tamanho);

    aplicandoFuncao(arr, tamanho, dobro);
    imprimir("Array dobrado:", arr, tamanho);

    return 0;
}