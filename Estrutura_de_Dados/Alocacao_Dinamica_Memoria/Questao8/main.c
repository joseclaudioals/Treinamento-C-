#include <stdio.h>
#include <stdlib.h>

typedef struct Aluno{
    int matricula;
    char nome[50];
}Aluno;

Aluno* realocarMemoria(int* capacidade, Aluno* ptr){
    Aluno* tempLista = ptr;
    *capacidade+=3;
    tempLista = realloc(ptr, sizeof(Aluno)* *capacidade);
    if(tempLista==NULL){
        printf("erro ao alocar memoria\n");
        free(tempLista);
        exit(1);
    }

    return tempLista;
}

int main(void){
    Aluno* listaAluno=NULL;
    int capacidade=3;
    int total=0;
    int opt;

    listaAluno = malloc(sizeof(Aluno)*capacidade);
    printf(">- Cadastro Alunos -<\n");
    do{
        if(capacidade == total){
            listaAluno=realocarMemoria(&capacidade, listaAluno);
        }
        printf("Aluno %i\n", total+1);
        printf("Matricula:");
        scanf(" %i", &listaAluno[total].matricula);
        printf("Nome:");
        scanf(" %s", listaAluno[total].nome);

        printf("Deseja cadastrar outro item?\nSIM [1]\nNAO [2]\n");
            scanf(" %i", &opt);

        total++;
    }while(opt==1);

    for(int i=0;i<total; i++){
        printf("ALUNO %i\nMatricula: %i\nNome: %s\n", i+1, listaAluno[i].matricula, listaAluno[i].nome);
    }
    free(listaAluno);
    listaAluno=NULL;
    return 0;
}