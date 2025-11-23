#include <stdio.h>
#include <stdlib.h>

typedef struct Carro{
    char modelo[20];
    char placa[20];
    int ano
}Carro;

int main(void){
    Carro* meuCarro = malloc(sizeof(Carro));

    if(meuCarro==NULL){
        printf("Falha catastrofica!\nErro na aloação\n");
        return 0;
    }

    printf(">> Cadastro Carro <<\n");
    printf("Insira o modelo:\n");
    scanf(" %s", meuCarro->modelo);
    printf("Insira a placa:\n");
    scanf(" %s", meuCarro->placa);
    printf("Insira o ano:\n");
    scanf(" %i", &meuCarro->ano);

    printf("\n>> Cadastro Carro <<\n");
    printf("Modelo: %s\n", meuCarro->modelo);
    printf("Placa: %s\n", meuCarro->placa);
    printf("Ano: %i\n", meuCarro->ano);

    free(meuCarro);

    meuCarro= NULL;
    return 0;
}