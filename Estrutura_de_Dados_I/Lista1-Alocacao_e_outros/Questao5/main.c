#include <stdio.h>
#include <stdlib.h>

typedef struct Retangulo{
    float altura;
    float largura;
}Retangulo;

Retangulo* copiarRetangulo(Retangulo original){
    Retangulo* tcpy = malloc(sizeof(Retangulo));
    tcpy->altura = original.altura;
    tcpy->largura = original.largura;

    return tcpy;
}

int main(void){
    Retangulo t1 = {6, 8};
    printf("Retangulo Original\nAltura:%.2f\nLargura: %.2f\n", t1.altura, t1.largura);

    Retangulo* tcpy = copiarRetangulo(t1);

    printf("Retangulo Copiado\nAltura:%.2f\nLargura: %.2f\n", tcpy->altura, tcpy->largura);

    free(tcpy);
    tcpy = NULL;

    return 0;
}