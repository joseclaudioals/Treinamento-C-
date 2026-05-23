#include <stdio.h>
#include <stdlib.h>

typedef struct Aluno{
    int matricula;
    char nome[50];
}Aluno;

Aluno* realocarMemoria(int* capacidade, Aluno* ptr);
void removerAluno(Aluno* listaAluno, int* total);
void adicionarAluno(int *total, int* capacidade, Aluno** listaAluno);
int buscarAluno(Aluno* lista, int matricula, int total);

int main(void){
    Aluno* listaAluno=NULL;
    int capacidade=3;
    int total=0;
    int opt;

    listaAluno = malloc(sizeof(Aluno)*capacidade);

    do{
        printf(">> CADASTRO ALUNO <<\n");
        printf("Adicionar aluno - 1\n");
        printf("Remover aluno --- 2\n");
        printf("Sair ------------ 3\n");
        scanf(" %i", &opt);

        switch(opt){
            case 1:
                adicionarAluno(&total, &capacidade, &listaAluno);
                break;
            case 2:
                removerAluno(listaAluno, &total);
                break;
            case 3:
                printf("Saindo do programa\n");
                break;
            default:
                printf("opcao invalida");
        }
    }while(opt!=3);

    for(int i=0;i<total; i++){
        printf("ALUNO %i\nMatricula: %i\nNome: %s\n", i+1, listaAluno[i].matricula, listaAluno[i].nome);
    }
    free(listaAluno);
    listaAluno=NULL;
    return 0;
}
Aluno* realocarMemoria(int* capacidade, Aluno* lista){
    Aluno* tempLista = lista;
    *capacidade+=3;
    tempLista = realloc(lista, sizeof(Aluno)* *capacidade);
    if(tempLista==NULL){
        printf("erro ao alocar memoria\n");
        free(tempLista);
        exit(1);
    }

    return tempLista;
}
void adicionarAluno(int *total, int* capacidade, Aluno** listaAluno){
    int opt=0;
    do{
        if(*capacidade == *total){
            *listaAluno=realocarMemoria(capacidade, *listaAluno);
        }
        printf("Aluno %i\n", (*total)+1);
        printf("Matricula:");
        scanf(" %i", &(*listaAluno)[*total].matricula);
        printf("Nome:");
        scanf(" %s", (*listaAluno)[*total].nome);

        printf("Deseja cadastrar outro item?\nSIM [1]\nNAO [2]\n");
            scanf(" %i", &opt);

        (*total)++;

    }while(opt==1);
}
void removerAluno(Aluno* listaAluno, int* total){
    int opt=0;
    printf("insira a matricula do aluno a ser removido:\n");
    scanf(" %i", &opt);

    int controle = buscarAluno(listaAluno, opt, *total);

    if(controle>=0 && controle<(*total)){
        for(int i=controle; i<(*total)-1; i++ ){
           listaAluno[i]=listaAluno[i+1];
        }
        (*total)--;
        printf("Aluno removido do sistema\n");
    }
    else
        printf("aluno nao encontrado\n");
}
int buscarAluno(Aluno* lista, int matricula, int total){
    for(int i=0; i<total; i++){
        if(matricula==lista[i].matricula)
            return i;
    }
    return -1;
}