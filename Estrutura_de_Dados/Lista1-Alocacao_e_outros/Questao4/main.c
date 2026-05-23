#include <stdio.h>
#include <stdlib.h>

typedef struct Produto{
    char nome[30];
    float preco;
    int quantidade;
}Produto;

void limparBuffer(){
    int c;
    while((c=getchar())!='\n' && c!=EOF){}
}

int main(void){
    Produto* estoque = malloc(5*sizeof(Produto));

    printf(">> ESTOQUE <<\n");
    for(int i=0; i<5; i++){
        printf("\n- Produto %i\n", i+1);
        printf("Insira o nome do produto:\n");
        scanf(" %s", estoque[i].nome);
        limparBuffer();

        printf("Insira o preco do produto:\n");
        scanf(" %f", &estoque[i].preco);

        printf("Insira a quantidade do produto:\n");
        scanf(" %i", &estoque[i].quantidade);
    }
    for(int i=0; i<5; i++){
        printf("\n- Produto %i\n", i+1);
        printf("Nome: %s\n",estoque[i].nome);
        printf("Preco: R$ %.2f\n", estoque[i].preco);
        printf("Quantidade: %i\n", estoque[i].quantidade);
    }

    free(estoque);
    estoque = NULL;
    return 0;
}