#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int id;
    char descricao[64];
    struct Node* proximo;
}Node;

void inserirAtividade(Node** head);
void listarAtividades(Node* head);
void limparLista(Node** head);

int main(void){
    Node* head=NULL;
    int opt;
    do{
        printf("Inserir atividade - 1\n");
        printf("Listar tarefas ---- 2\n");
        printf("Limpar lista ------ 3\n");
        printf("sair -------------- 0\n");
        scanf(" %i", &opt);
        switch(opt){
            case 1: 
                inserirAtividade(&head);
                break;
            case 2:
                listarAtividades(head);
                break;
            case 3:
                limparLista(&head);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida\n");
        }
    }while(opt!=0);

    limparLista(&head);
    return 0;
}

void inserirAtividade(Node** head){
    Node* atv = malloc(sizeof(Node));
        
    if(atv==NULL){
        printf("erro ao alocar atividade\n");
        return;
    }
    
    printf("Insira uma descrição da atividade\n");
    scanf(" %50[^\n]", atv->descricao);
    printf("Insira o id da atividade\n");
    scanf(" %i", &atv->id);

    atv->proximo=NULL;

    if(*head==NULL){
        *head = atv;
        return;
    }
    
    Node* ultimo = *head;
    while(ultimo->proximo!=NULL){
        ultimo = ultimo->proximo;
    }
    ultimo->proximo=atv;
    
}

void listarAtividades(Node* head){
    Node* temp = head;
    while(temp!=NULL){
        printf("Id: %i\n", temp->id);
        printf("Descricao: %s\n", temp->descricao);
        temp=temp->proximo;
    }
}

void limparLista(Node** head){
    Node* atual = *head;
    Node* proximo;

    while(atual!=NULL){
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *head=NULL;
    printf("memoria liberada");
}