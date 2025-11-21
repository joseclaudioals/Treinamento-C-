#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int valor;
    struct Node *proxNode;
}Node;

Node *head=NULL;

void inserirNode();
void removerNode();
void imprimirTodos();

int main(void){
    int opt;
    do{
        printf("inserir node - 1\n");
        printf("remover node - 2\n");
        printf("imprimir todos node - 3\n");
        printf("sair - 4\n");
        scanf(" %i", &opt);

        switch(opt){
            case 1:
                inserirNode();
                break;
            case 2:
                removerNode();
                break;
            case 3:
                imprimirTodos();
                break;
            case 4:
                printf("encerrando programa\n");
                break;
        }
    }while(opt!=4);

    limparNodes();
    
    return 0;
}

void inserirNode(){
    Node *novoNode = malloc(sizeof(Node));
    if(novoNode == NULL){
        printf("falha na alocacao\n");
        return;
    }
    printf("node criado com sucesso!\n");

    printf("insira um valor inteiro\n");
    scanf(" %i", &(novoNode->valor));

    novoNode->proxNode = NULL;

    if(head==NULL){
        head=novoNode;
        return;
    }
    

    Node *ultimo = head;
    while(ultimo->proxNode!=NULL){
        ultimo=ultimo->proxNode;
    }

    ultimo->proxNode=novoNode;
    
}
void removerNode(){
    int posicao;
    printf("qual a posicao do node a ser removido?\n");
    scanf(" %i", &posicao);

    if(head == NULL){
        printf("lista vazia, nada a remover\n");
        return;
    }

    Node *temp = NULL;

    if(posicao==0){
        temp = head;
        head = temp->proxNode;
    }
    else{
        Node *nodeAnterior = head;
        for(int i=0; nodeAnterior != NULL && i<posicao-1;i++){
            nodeAnterior = nodeAnterior->proxNode;
        }
        if(nodeAnterior == NULL || nodeAnterior->proxNode == NULL){
            // se o nodeAnterior é um valor fora da lista 
            //ou se nodeAnteior é o ultimo valor da lista 
            printf("erro: posicao %i invalida!\n", posicao);
            return;
        }
        // temp recebe o node que será removido
        temp = nodeAnterior->proxNode; 
        nodeAnterior->proxNode=temp->proxNode; 
        // nodeAnterior se conecta ao node seguinte ao que será removido
        //ex: node 4 será removido
        //nodeAnterior = node 3
        //temp = node 4
        //nodeAnterior -> proxNode = node 5  
        //o antigo node 5 se torna o node 4
    }
    if(temp!=NULL){
        printf("Node com valor %i removido\n", temp->valor);
        free(temp);
    }
}
void imprimirTodos(){
    Node *temp = head;
    if(temp == NULL){
        printf("lista vazia\n");
        return;
    }
    for(int i=0; temp!=NULL ; i++){
        printf("NODE %i\n", i);
        printf("valor: %i\n", temp->valor);
        temp = temp->proxNode;
    }
}
void limparNodes(){
    Node *noAtual = head;
    Node *proximo;

    while(noAtual!=NULL){
        proximo = noAtual->proxNode;
        free(noAtual);
        noAtual = proximo;
    }

    head = NULL;
}