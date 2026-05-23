#include <stdio.h>
#include <stdlib.h>

typedef struct Aluno{
    char nome[50];
    int matricula;
}Aluno;

void adicionarAluno(Aluno*** listaAlunos, int* capacidade, int* total);
void limparBuffer();
void alocarMemoria(int *capacidade, Aluno*** listaAlunos );

int main(void){
    Aluno** listaAlunos = NULL;
    int capacidade = 3;
    int total = 0;
    int opt=0;

    listaAlunos = malloc(capacidade*sizeof(Aluno*));

    if(listaAlunos==NULL){
        printf("Erro catastrofico! Erro ao alocar memoria\n");
        exit(1);
    }

    do{
        printf(">> CADASTRO ALUNO <<\n");
        printf("Adicionar aluno -- 1\n");
        printf("Remover aluno ---- 2\n");
        printf("Otimizar memoria - 3\n");
        printf("Sair ------------- 4\n");
        scanf(" %i", &opt);

        switch(opt){
            case 1:
                adicionarAluno(&listaAlunos, &capacidade, &total);
                break;
            case 2:
                //removerAluno();
                break;
            case 3:
                //otimizarMemoria();
                break;
            case 4:
                printf("Saindo do programa\n");
                break;
            default:
                printf("opcao invalida\n");
        }
    }while(opt!=4);

    printf("\n>> Cadastro Alunos <<\n");
    for(int i=0; i<total;i++){
        printf("\nAluno %i\nMatricula: %i\nNome: %s\n", i+1, listaAlunos[i]->matricula, listaAlunos[i]->nome);
    }

    for(int i=0; i<total; i++){
        free(listaAlunos[i]);
    }

    free(listaAlunos);
    listaAlunos=NULL;
    return 0;
}


void adicionarAluno(Aluno*** listaAlunos, int* capacidade, int* total){
    int opt=0;
    do{
        if(*total==*capacidade){
            alocarMemoria(capacidade, listaAlunos);
        }

        (*listaAlunos)[*total]=malloc(sizeof(Aluno));

        printf("\nAluno %i", *total+1);
        printf("\nMatricula: ");
        scanf(" %i", &(*listaAlunos)[*total]->matricula);
        limparBuffer();
        printf("Nome: ");
        scanf(" %s", (*listaAlunos)[*total]->nome);
        limparBuffer();

        printf("Deseja realizar outro cadastro?\n");
        printf("Sim [1] | Nao [0]");
        scanf(" %i", &opt);

        (*total)++;

    }while(opt==1);
}
void limparBuffer(){
    int c;
    while((c=getchar())!='\n' && c != EOF){}
}
 void alocarMemoria(int *capacidade, Aluno*** listaAlunos ){
    (*capacidade)+=3;

    Aluno** tempCadastro = realloc(*listaAlunos, sizeof(Aluno*)*(*capacidade));
    if(tempCadastro==NULL){
        printf("Erro catastrofico ao realocar memoria");
        exit(1);
    }
    printf("\n memoria alocada com sucesso \n");

    *listaAlunos = tempCadastro;
}

void removerAluno(Aluno** listaAluno, int* total){
    int matricula;
    printf("Digite a matricula do aluno a ser removido\n");
    scanf(" %i", &matricula);

    int indice = buscarAluno(listaAluno, *total, matricula);

    if(indice>=0){
        free(listaAluno[indice]);
        for(int i = indice ; i<(*total)-1; i++){
            listaAluno[i]=listaAluno[i+1];
        }
        
        (*total)--;
        listaAluno[(*total)-1]=NULL;
        printf("aluno removido com sucesso\n");
    }
    else{
        printf("falha ao remover aluno");
    }
}

int buscarAluno(Aluno** listaAluno, int total, int matricula){
    for(int i=0; i<total; i++){
        if(listaAluno[i]->matricula==matricula){
            return i;
        }
    }
    return -1;
}


/* void realocarMemoria(){
    
}  */




