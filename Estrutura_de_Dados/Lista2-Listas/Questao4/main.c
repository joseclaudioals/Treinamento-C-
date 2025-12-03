#include <stdio.h>
#include <stdlib.h>

typedef struct Aluno{
    char nome[21];
    float nota;
    struct Aluno* proximo;
}Aluno;

void adicionarNota(Aluno** head);
void imprimirLista(Aluno* head);
void liberarLista(Aluno **head);

int main(void){
    Aluno* head=NULL;
    int opt;
    do{
        printf("adicionar aluno ---- 1\n");
        printf("imprimir notas - --- 2\n");
        printf("sair --------------- 0\n");
        scanf(" %i", &opt);
        switch(opt){
            case 1: 
                adicionarNota(&head);
                break;
            case 2:
                imprimirLista(head);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida\n");
        }
    }while(opt!=0);

    liberarLista(&head);

    return 0;
}

void adicionarNota(Aluno** head){
    Aluno* novoAluno = malloc(sizeof(Aluno));

    if(novoAluno==NULL){
        printf("erro de alocacao\n");
        return;
    }

    printf("insira nome do aluno:\n");
    scanf(" %20[^\n]", novoAluno->nome);
    printf("insira nota do aluno\n");
    scanf(" %f", &novoAluno->nota);

    if(*head==NULL){
        novoAluno->proximo = *head;
        *head = novoAluno;
        return;
    }

    Aluno* anterior=NULL;
    Aluno* atual = *head;

    while(atual!=NULL && novoAluno->nota<atual->nota){
        anterior = atual;
        atual = atual->proximo;
    }

    if(anterior==NULL){
        novoAluno->proximo = *head;
        *head = novoAluno;
        return;
    }

    anterior->proximo = novoAluno;
    novoAluno->proximo = atual;
}

void imprimirLista(Aluno* head){
    Aluno* atual = head;
    Aluno* proximo;

    while(atual!=NULL){
        printf("Aluno: %s\n", atual->nome);
        printf("Nota: %.2f\n", atual->nota);
        proximo = atual->proximo;
        atual = proximo;
    }
}

void liberarLista(Aluno **head){
    Aluno* atual = *head;
    Aluno* proximo;

    while(atual!=NULL){
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    *head = NULL;
}