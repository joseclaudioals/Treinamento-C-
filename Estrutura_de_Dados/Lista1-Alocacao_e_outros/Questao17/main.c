#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livro{
    char titulo[50];
    int ano;
}Livro;

typedef struct Autor{
    char nome[50];
    Livro *livros;
    int totalLivros;
    int capacidadeLivros;
}Autor;

void addAutor(Autor** colecaoAutores, int* total, int* capacidade);
int alocarAutor(Autor** colecaoAutores, int total);
void addLivroAutor(Autor* colecaoAutores, int total);
int busca(char nome[50], int total, Autor* colecaoAutores);

int main(void){
    Autor* colecaoAutores=NULL;
    int total=0;
    int capacidade=3;
    

    addAutor(&colecaoAutores, &total, &capacidade);
    addLivroAutor(colecaoAutores, total);
    
}

void addAutor(Autor** colecaoAutores, int* total, int* capacidade){
    int opt;
    do{
        int i = (*total);
        (*total)++;
        if(alocarAutor(colecaoAutores, *total)){
            printf("Insira o nome do autor:\n");
            scanf(" %s", colecaoAutores[i]->nome);
            printf("Insira a capacidade de livros do autor\n");
            scanf(" %i", &colecaoAutores[i]->capacidadeLivros);
            colecaoAutores[*total]->totalLivros=0;
            
        }
        else{
            printf("nao foi possivel cadastrar autor\n");
        }
            
        printf("Deseja repertir a operacao?\nsim[1] nao[0]\n");
        scanf(" %i", &opt);
    }while(opt==1);
}

int alocarAutor(Autor** colecaoAutores, int total){
    Autor* tempArray = NULL;
    tempArray=realloc(*colecaoAutores, sizeof(Autor)*total);
    if(tempArray==NULL){
        printf("memoria nao alocada\n");
        return 0;
    }
    printf("memoria alocada com sucesso\n");
    *colecaoAutores=tempArray;
    return 1;

}

void addLivroAutor(Autor* colecaoAutores, int total){
    char tempNome[50];
    
    printf("qual o nome do autor?\n");
    scanf(" %s", tempNome);

    int i = busca(tempNome, total, colecaoAutores);

    colecaoAutores[i].livros=malloc(sizeof(Livro)*colecaoAutores[i].capacidadeLivros);

    for(int j=0; j< colecaoAutores[i].capacidadeLivros; j++){
        printf("insira o titulo do livro do autor %s\n", colecaoAutores[i].nome);
        scanf("%s", *colecaoAutores[i].livros[j].titulo);
        printf("insira o ano do livro:\n");
        scanf(" %i", &colecaoAutores[i].livros[j].ano);
    }
}

int busca(char nome[50], int total, Autor* colecaoAutores){
    for(int i=0; i<total; i++){
        if(strcmp(nome, colecaoAutores[i].nome))
            return i;
    }
    return -1;
}