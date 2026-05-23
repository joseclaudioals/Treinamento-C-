#include <stdio.h>
#include <stdlib.h>

typedef struct Pessoa{
    char nome[50];
    int idade;
}Pessoa;

typedef struct Node{
    Pessoa* pessoa;
    struct Node* proximo;
}Node;

void limparBuffer();
void inserirInicio(Node** head);
void liberarLista(Node** head);

int main(void){
    Node* head = NULL;
    
    inserirInicio(&head);
    liberarLista(&head);
    
    return 0;
}
void limparBuffer(){
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

void inserirInicio(Node** head){
    int opt;
    do{
        Pessoa* p = malloc(sizeof(Pessoa));
        
        if(p==NULL){
            printf("erro ao alocar memoria\n");
            return;
        }
        
        printf("Insira o nome da pessoa\n");
        scanf(" %s", p->nome);
        limparBuffer();
        
        printf("insira a idade da pessoa\n");
        scanf(" %i", &p->idade);
        limparBuffer();
        
        Node* novoNode = malloc(sizeof(Node));
        
        if(novoNode==NULL){
            printf("erro ao alocar memoria\n");
            return;
        }
        novoNode->pessoa=p;
        novoNode->proximo=*head;
        *head = novoNode;
        
        printf("Deseja repetir a operacao?\nsim[1] nao[0]\n");
        scanf(" %i", &opt);
    }while(opt==1);
}

void liberarLista(Node** head){
    Node* atual = *head;
    Node* proximo;
    
    while(atual!=NULL){
        free(atual->pessoa);
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    printf("memoria liberada");
    *head = NULL;
}
