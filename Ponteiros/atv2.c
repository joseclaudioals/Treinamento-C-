/*Escreva uma função chamada incrementar_ponteiro. Esta função deve receber um ponteiro para um inteiro como argumento. Dentro da função, o valor da variável para a qual o ponteiro aponta deve ser incrementado em 10. Na função main, declare uma variável inteira, imprima seu valor inicial, chame a função incrementar_ponteiro passando o endereço da variável e, por fim, imprima o valor final da variável para confirmar a modificação.*/

#include <stdio.h>

void incrementarN(int *nP){
    *nP+=10;
}

int main(void){
    int n = 10;
    //verificando o valor original de N
    printf("valor de n = %i\n", n);
    //chamada de função
    incrementarN(&n);
    //verificando valor pós chamada de N
    printf("novo valor de n = %i\n", n);

    return 0;
}