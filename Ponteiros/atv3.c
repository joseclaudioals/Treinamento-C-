/*Crie uma função chamada calcular_soma_e_produto que recebe dois números inteiros e dois ponteiros para inteiros. A função deve calcular a soma e o produto dos dois números recebidos e armazenar os resultados nos endereços de memória apontados pelos ponteiros.

*/

#include <stdio.h>

void calculos(int a, int b, int* produto, int* soma){
    *produto = a * b;
    *soma = a + b;
}

int main(void){
    int n1 = 2, n2 = 5, produto, soma;

    calculos(n1, n2, &produto, &soma);

    printf("%i + %i = %i\n", n1, n2, soma);
    printf("%i x %i = %i", n1, n2, produto);
}