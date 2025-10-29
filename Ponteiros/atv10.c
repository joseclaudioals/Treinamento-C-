/*Crie uma função que recebe um ponteiro para um float. A função deve verificar se o ponteiro é nulo (NULL). Se não for nulo, a função deve dobrar o valor para o qual ele aponta e retornar 1 (sucesso). Se o ponteiro for nulo, a função não deve fazer nada e retornar 0 (falha).*/

#include <stdio.h>
int ehnulo(float* n){
    if(n !=NULL){
        *n = *n * 2;
        return 1;
    }
    else 
        return 0;
}
int main(void){
    float n = 2.5;
    float *pN = &n;
    int verif;

    verif = ehnulo(pN);

    if(verif)
        printf("ponteiro aponta pra algo, valor de n dobrado para %.2f", *pN);
        else
            printf("valor nulo");

    return 0;
}