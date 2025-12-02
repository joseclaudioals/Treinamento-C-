#include <stdio.h>
#include <stdlib.h>

typedef struct Documento{
    char nome[50];
    int paginas;
    struct Documento* proximo;
}Documento;

typedef struct Fila{
    Documento* inicio;
    Documento* fim;
}Fila;

int main(void){
    Fila* filaImpressora;
    int opt;

    incializarFila(&filaImpressora);

    do{
        printf("adicionar documento - 1\n");
        printf("imprimir ------------ 2\n");
        printf("sair --------------- 0\n");
        scanf(" %i", &opt);
        switch(opt){
            case 1: 
                
                break;
            case 2:
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida\n");
        }
        
    }while(opt!=0);


    return 0;
}

void incializarFila(Fila* f){
    f->fim = NULL;
    f->inicio = NULL;
}

void adicionarDocumento(Fila* f){
    Documento* novoDocumento = malloc(sizeof(Documento));

    if(novoDocumento==NULL){
        printf("Erro ao alocar memoria\n");
        return;
    }

    printf("Insira o nome do arquivo:\n");
    scanf(" %20[^\n]", novoDocumento->nome);
    printf("Insira a quantidade de paginas:\n");
    scanf(" %i", &novoDocumento->paginas);

    novoDocumento->proximo=NULL;

    if(f->inicio==NULL){
        f->inicio=novoDocumento;
        f->fim=novoDocumento;
        return;
    }

    f->fim->proximo=novoDocumento; //ligo o antigo ultimo com o novo ultimo
    f->fim=novoDocumento; //novo documento é o novo fim da lista
}

void imprimir(Fila* f){
    if(f->inicio==NULL){
        printf("Lista vazia\n");
        return;
    }

    Documento* temp = f->inicio;
    printf("Imprimindo %s\n", temp->nome);
    f->inicio=temp->proximo;

    if(f->inicio==NULL){ //tratando fila com apenas um elemento
        f->fim;
    }

    free(temp);
}

void liberarFila(Fila* f){
    Documento* atual = f->inicio;
    Documento* proximo;

    while(atual!=NULL){
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    f->fim=NULL;
    f->inicio=NULL;

    printf("memoria liberada\n");
}