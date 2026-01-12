#include <stdio.h>
#include <stdlib.h>

typedef struct Musica{
    char nome[50];
    struct Musica* proximo;
    struct Musica* anterior;
}Musica;

void limparBuffer();
void adicionarMusica(Musica** head, Musica** mAtual);
void avancarMusica(Musica** mAtual);
void voltarMusica(Musica** mAtual);
void liberarLista(Musica** head);

int main(void){
    Musica* head=NULL;
    Musica* musicaAtual=NULL;

   int opt;
    do{
        printf("adicionar musica ---- 1\n");
        printf("avancar musica ------ 2\n");
        printf("voltar musica ------- 3\n");
        printf("sair ---------------- 0\n");
        scanf(" %i", &opt);
        switch(opt){
            case 1: 
                adicionarMusica(&head, &musicaAtual);
                break;
            case 2:
                avancarMusica(&musicaAtual);
                break;
            case 3:
                voltarMusica(&musicaAtual);
            case 0:
                break;
            default:
                printf("Opcao invalida\n");
        }
        printf("\n --- Tocando %s --- \n", musicaAtual->nome);
    }while(opt!=0);

    liberarLista(&head);

    return 0;
}

void limparBuffer(){
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

void adicionarMusica(Musica** head, Musica** mAtual){
    Musica* novaMusica = malloc(sizeof(Musica));

    if(novaMusica==NULL){
        printf("erro ao alocar memoria\n");
        return;
    }

    printf("Qual o nome da musica?\n");
    scanf(" %49[^\n]", novaMusica->nome);

    limparBuffer();

    novaMusica->proximo=NULL;

    if(*head==NULL){
        novaMusica->anterior=NULL;
        *head = novaMusica;
        *mAtual = novaMusica;

        return;
    }

    Musica* ultimo = *head;

    while(ultimo->proximo!=NULL){
        ultimo = ultimo->proximo;
    }

    ultimo->proximo = novaMusica;
    novaMusica->anterior=ultimo;

}

void avancarMusica(Musica** mAtual){
    if((*mAtual)->proximo == NULL){
        printf("Nao ha musica para avançar\n");
        return;
    }
    *mAtual = (*mAtual)->proximo;
}

void voltarMusica(Musica** mAtual){
    if((*mAtual)->anterior==NULL){
        printf("Nao ha musicas para voltar\n");
        return;
    }
    *mAtual = (*mAtual)->anterior;

}

void liberarLista(Musica** head){
    Musica* atual = *head;
    Musica* proximo;
    while(atual!=NULL){
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    *head = NULL;
}