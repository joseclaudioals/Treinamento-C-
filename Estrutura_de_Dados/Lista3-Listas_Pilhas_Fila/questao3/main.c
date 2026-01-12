#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -- structs 

typedef struct node{
    char titulo[20];
    int id;
    struct node* proximo;
}node;

typedef struct playlist{
    node* inicio;
    node* fim;
}playlist;

// -- funções de manipulação 
void adicionarMusica(int id, char titulo[20], playlist* p);
int percorrerLista(int id, playlist* p);
void trocarPosicao(int id1, int id2, playlist* p);
node* buscarId(int id, playlist* p);
void imprimirPlaylist(playlist* p);
void limparPlaylist(playlist* p);
void limparBuffer();

int main(void){

    playlist p;
    p.inicio = NULL;
    p.fim = NULL;

    int opt;

    do{
        printf("1 - adicionar musica\n2 - trocar posicao musica\n3 - imprimir lista\n0 - sair\n");
        scanf(" %i", &opt);
        limparBuffer();

        switch(opt){
            case 1:{
                printf("insira o titulo da musica\n");
                char temp[20];
                scanf("%[^\n]", temp);
                limparBuffer();

                printf("insira o id da musica\n");
                int id;
                scanf(" %i", &id);
                limparBuffer();

                adicionarMusica(id, temp, &p);
                break;
            }
            case 2:{
                printf("insira o id da musica1\n");
                int id1;
                scanf(" %i", &id1);
                limparBuffer();

                printf("insira o id da musica2\n");
                int id2;
                scanf(" %i", &id2);
                limparBuffer();

                trocarPosicao(id1, id2, &p);
                break;
            }
            case 3:
                imprimirPlaylist(&p);
                break;
            case 0:
                break;
            default:
                printf("Insira uma opcao valida\n");
        }

    }while(opt!=0);

    limparPlaylist(&p);

    return 0;
}

void adicionarMusica(int id, char titulo[20], playlist* p){
    if(percorrerLista(id, p)){
        printf("adicionando musica...\n");

        node* musica = malloc(sizeof(node));
        if(musica == NULL){
            printf("nao foi possivel adicionar a musica.\n");
            return;
        }

        musica->id = id;
        strcpy(musica->titulo, titulo); // nao podemos atribuir strings em c, usamos strcpy
        musica->proximo=NULL;

        if((p->inicio)==NULL){
            p->inicio=musica;
            p->fim=musica;
            return;
        }

        p->fim->proximo = musica;
        p->fim=musica;
    }
    else{
        printf("Musica com mesmo id já existente\nImpossivel adicionar\n");
    }
}

int percorrerLista(int id, playlist* p){
    if(p->inicio==NULL){
        printf("playlist vazia\n");
        return 1;
    }
    node* temp = p->inicio;
    while(temp!=NULL){
        if(temp->id==id)
            return 0;
        temp = temp->proximo;
    }

    return 1;
}

void trocarPosicao(int id1, int id2, playlist* p){
    if(p->inicio==NULL){
        printf("playlist vazia\n");
        return;
    }

    node* musica1 = buscarId(id1, p);
    if(musica1 == NULL){
        printf("musica de id %i nao existente\n", id1);
        return;
    }

    node* musica2 = buscarId(id2, p);
    if(musica2 == NULL){
        printf("musica de id %i nao existente\n", id2);
        return;
    }

    //note que essa é uma operação mais custosa pro processador que uma troca de ponteiros 

    char tituloT[20]; 

    strcpy(tituloT, musica1->titulo);
    int idt = musica1->id;

    musica1->id = musica2->id;
    strcpy(musica1->titulo, musica2->titulo);

    musica2->id = idt;
    strcpy(musica2->titulo, tituloT);

    printf("musicas trocadas de lugar\n");
}

node* buscarId(int id, playlist* p){
    node* temp = p->inicio;
    node* musica=NULL;
    while(temp!=NULL){
        if((temp->id)==id){
            musica = temp;
            break;
        }
        temp = temp->proximo;
    }
    return musica;
}

void imprimirPlaylist(playlist* p){
    if((p->inicio)==NULL){
        printf("playlist vazia\n");
        return;
    }

    node* temp = p->inicio;
    while(temp!=NULL){
        printf("Musica: %s | ID: %i\n", temp->titulo, temp->id);
        temp = temp->proximo;
    }
}

void limparPlaylist(playlist* p){
    if((p->inicio)==NULL){
        printf("playlist vazia\n");
        return;
    }

    node* temp = p->inicio;
    while(temp!=NULL){
        node* aux = temp;
        temp = temp->proximo;
        free(aux);
    }

    printf("playlist limpa\n");
}

void limparBuffer(){
    char c;
    while((c=getchar())!='\n' && c!= EOF){}
}