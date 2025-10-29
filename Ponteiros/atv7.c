/*
    Crie uma função chamada trocar_ponteiros. Ela deve receber dois ponteiros para ponteiros de inteiro (int **). A função deve trocar os endereços armazenados nos dois ponteiros originais.
*/

#include <stdio.h>

void swapP(int **aP, int **bP){
    int *aux;
    printf("a = %p | b = %p\n", aP, bP);
    aux = *aP;
    *aP = *bP;
    *bP = aux;
}

int main(void){
    int a=2, b=10;
    int *aP=&a, *bP=&b;

    printf("VALORES INICIAIS\n");
    printf("ponteiro A: valor %i | endereco %p\n", *aP, aP);
    printf("ponteiro B: valor %i | endereco %p\n", *bP, bP);

    swapP(&aP, &bP);

    printf("VALORES FINAIS\n");
    printf("ponteiro A: valor %i | endereco %p\n", *aP, aP);
    printf("ponteiro B: valor %i | endereco %p\n", *bP, bP);

    return 0;
}