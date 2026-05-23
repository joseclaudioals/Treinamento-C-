#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char url[80];
   struct Node* proximo;
}Node;

typedef struct Pilha{
    Node* topo;
}Pilha;

void iniciarPilha(Pilha* p);
void visitarPagina(Pilha* p);
char* voltarPagina(Pilha* p);
void liberarPilha(Pilha* f);


int main(void){
    Pilha p;
    iniciarPilha(&p);

    int opt;
    do{
        printf("Visitar pagina - 1\n");
        printf("voltar pagina ---- 2\n");
        printf("sair -------------- 0\n");
        scanf(" %i", &opt);
        switch(opt){
            case 1: 
                visitarPagina(&p);
                break;
            case 2:{
                char* url = voltarPagina(&p);
                
                printf("pagina anterior: %s\n", url);
                if(p.topo!=NULL)
                    printf("pagina atual: %s\n", p.topo->url);

                free(url);
                break;
            }
            case 0:
                break;
            default:
                printf("Opcao invalida\n");
        }
        
    }while(opt!=0);

    liberarPilha(&p);
    
    return 0;
}

void iniciarPilha(Pilha* p){
    p->topo=NULL;
}

void visitarPagina(Pilha* p){ //mesma coisa que push
    Node* novoNode=malloc(sizeof(Node));
    if(novoNode==NULL){
        printf("Erro ao alocar memoria\n");
        return;
    }

    printf("Insira a url visitada\n");
    scanf(" %79[^\n]", novoNode->url);

    printf("Node criado com sucesso\n");

    novoNode->proximo=p->topo;
    p->topo=novoNode;
}

char* voltarPagina(Pilha* p){ //mesma coisa que pop
    if(p->topo==NULL){
        printf("pilha vazia\n");
        return NULL;
    }
    Node* temp = p->topo;

    char* url = malloc(strlen(temp->url)+2);
    if(url==NULL) return NULL;
    
    strcpy(url, temp->url);

    p->topo = temp->proximo;
    free(temp);

    return url;

}

void liberarPilha(Pilha* f){
    Node* atual = f->topo;
    Node* proximo;

    while(atual!=NULL){
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    f->topo=NULL;

    printf("memoria liberada\n");
}