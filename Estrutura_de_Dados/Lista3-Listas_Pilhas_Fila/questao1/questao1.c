//considerarei o usuário inteligente

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    float valor;
    struct node* proximo;
}node;

typedef struct pilha{
    struct node* topo;
}pilha;

int verificaOperando(char* str);

int main(void){

    char str[20];
    char* operadores=NULL;
    
    operadores = malloc(sizeof(char)*1);

    int tamanho_op = sizeof(operadores);

    // iniciando a pilha 
    pilha p;
    p.topo=NULL;

    push(0, &p);

    // recebendo digitos

    printf("digite a expressao:");
    scanf(" %[^\n]", &str);

    char* tokens = strtok(str, " ");

    while(tokens != NULL){
        printf("%s\n", tokens);

        float valor = strtof(tokens, NULL);
        printf("%.2f\n", valor);

        tokens = strtok(NULL, " ");
    }
    
    return 0;
}

int verificaOperando(char* str){
    if(strcmp(str, "+")==0 || strcmp(str, "-")==0 || strcmp(str, "*")==0 || strcmp(str, "/")==0 )
        return 1;

    return 0;
}

void push(float valor, pilha* p){
    node* n = sizeof(node);

    if(n==NULL){
        printf("Erro ao alocar memoria\n");
        exit(0);
    }

    n->valor = valor;
    n->proximo = p->topo;
    p-> topo = n;
}

float pop(pilha* p){
    node* temp = p->topo;
    float valor = temp->valor;
    p->topo = temp->proximo;
    free(temp);

    return valor;
}