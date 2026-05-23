#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente{
    char nome[16];
    int numeroProtocolo;
    struct cliente* proximo;
}cliente;

typedef struct fila{
    cliente* inicio;
    cliente* fim;
}fila;

void incluirCliente(fila* f, int* cod);
void furarFila(fila* f, int* cod);
void atenderProx(fila* f);
void imprimirFila(fila* f);
void limparFila(fila* f);
void limparBuffer();

int main(void){
    fila f;
    f.inicio=NULL;
    f.fim=NULL;

    int codProtocolo = 0;

    int opt;

    do{
        printf("1 - inserir na fila\n2 - furar fila\n3 - atender\n4 - imprimir\n0 - sair\n");
        scanf(" %i", &opt);
        limparBuffer();

        switch(opt){
            case 1:
                incluirCliente(&f, &codProtocolo);
                break;
            case 2:
                furarFila(&f, &codProtocolo);
                break;
            case 3:
                atenderProx(&f);
                break;
            case 4:
                imprimirFila(&f);
            case 0:
                printf("saindo do sistema\n"); 
                break;
            default:
                printf("escolha uma opcao valida\n");
        }
    }while(opt!=0);

    limparFila(&f);

    return 0;
}

void incluirCliente(fila* f, int* cod){
    cliente* c = malloc(sizeof(cliente));

    if(c == NULL){
       printf("Erro ao alocar cliente\n");
       return; 
    }

    (*cod)++;

    printf("insira o nome do cliente\n");
    scanf(" %[^\n]", c->nome);
    limparBuffer();
    c->numeroProtocolo=(*cod);

    c->proximo = NULL;

    if(f->inicio==NULL){
        f->inicio=c;
        f->fim=c;
        return;
    }

    f->fim->proximo=c;
    f->fim=c;
}

void furarFila(fila* f, int* cod){
    cliente* c = malloc(sizeof(cliente));

    if(c == NULL){
       printf("Erro ao alocar cliente\n");
       return; 
    }

    (*cod)++;

    printf("insira o nome do cliente\n");
    scanf(" %[^\n]", c->nome);
    limparBuffer();
    c->numeroProtocolo=(*cod);

    if(f->inicio==NULL){
        c->proximo=NULL;
        f->inicio=c;
        f->fim=c;
        return;
    }

    c->proximo=f->inicio;
    f->inicio=c;

}

void atenderProx(fila* f){
    printf("Atendendo: %s\n", f->inicio->nome);

    cliente* temp = f->inicio;
    f->inicio=f->inicio->proximo;
    free(temp);

    printf("atendimento concluido\n");
}

void imprimirFila(fila* f){
    if(f->inicio==NULL){
        printf("fila vazia\n");
        return;
    }

    cliente* temp = f->inicio;

    while(temp!=NULL){
        printf("Nome: %s | Numero de Protocolo: %i\n", temp->nome, temp->numeroProtocolo);
        temp = temp->proximo;
    }
}

void limparFila(fila* f){
    cliente* temp = f->inicio;
    while(temp!=NULL){
        cliente* aux = temp;
        temp = temp->proximo;
        free(aux);
    }
}

void limparBuffer(){
    char c;
    while((c=getchar())!='\n' && c!=EOF){}
}


