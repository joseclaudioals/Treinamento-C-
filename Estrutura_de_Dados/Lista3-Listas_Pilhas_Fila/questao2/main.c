#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
   char texto[30];
   struct node* proximo;
}node;

typedef struct pilha{
    struct node* topo;
}pilha;

void escrever(pilha* p, char* texto);
void desfazer(pilha* p);
void mostrarTexto(pilha* p);
void limparP(pilha* p);
void limparBuffer();

int main(void){
    pilha p;
    p.topo=NULL;
    int opt;

    do{
        printf("1 - escrever\n2 - desfazer\n3-imprimir\n0 - sair\n");
        scanf(" %i", &opt);

        switch(opt){
            case 1:{
                char temp[30];
                scanf(" %[^\n]", temp);
                printf("%s\n", temp);
                limparBuffer();
                escrever(&p, temp);
                break;
            }
            case 2:
                desfazer(&p);
                break;
            case 3:
                mostrarTexto(&p);
                break;
            case 0:
                break;
            default:
                printf("Digite uma opcao valida\n");
    }
    }while(opt!=0);

    limparP(&p);

    printf("Texto limpo com sucesso");

    return 0;
}

void escrever(pilha* p, char* texto){
    node* novoNode = malloc(sizeof(node));

    if(novoNode==NULL){
        printf("erro ao alocar memoria para frase\nencerrando editor");
        exit(1);
    }

    strcpy(novoNode->texto, texto);

    novoNode->proximo= p->topo;
    p->topo=novoNode;
}

void desfazer(pilha* p){ // desfazer
    if(p->topo==NULL){
        printf("nenhum texto digitado\n");
        return;
    }

    node* temp = p->topo;
    printf("frase: \" %s \" removido\n", temp->texto);
    p->topo = temp->proximo;
    free(temp);
}

void mostrarTexto(pilha* p){
    pilha aux;
    aux.topo=NULL;

    node* temp=p->topo;
    while(temp!=NULL){
        escrever(&aux, temp->texto);
        node* aux = temp;
        temp = aux -> proximo;
    }

    temp = aux.topo;
    while(temp!=NULL){
        printf("%s \n", temp->texto);
        temp = temp -> proximo;
    }

    limparP(&aux);

}

void limparP(pilha* p){
    if(p->topo==NULL)
        return;

    while(p->topo!=NULL){
        node* temp = p->topo;
        p->topo = temp->proximo;
        free(temp);
    }
}

void limparBuffer(){
    char c;
    while((c=getchar())!='\n' && c!=EOF){}
}
