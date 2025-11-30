#include <stdio.h>
#include <stdlib.h>

typedef struct Pessoa{
    char nome[20];
    int idade;
}Pessoa;

void limparBuffer();
void adicionarPessoa(Pessoa** listaPessoa, int* total, int* capacidade);
void otimizarMemoria(Pessoa*** listaPessoa, int total, int* capacidade);

int main(void){
    Pessoa** listaPessoa = NULL;
    int capacidade = 3;
    int total = 0;
    int opt=0;
    listaPessoa = malloc(capacidade * sizeof(Pessoa*));

    if(listaPessoa==NULL){
        printf("erro ao alocar memoria\n");
        return 1;
    }

    do{    
        printf("Adicionar Pessoa - 1\n");
        printf("Otimizar memoria - 2\n");
        printf("Sair ------------- 0\n");
        scanf(" %i", &opt);

        switch(opt){
            case 1:
                adicionarPessoa(listaPessoa, &total, &capacidade);
                break;
            case 2:
                otimizarMemoria(&listaPessoa, total, &capacidade);
                break;
            case 0:
                printf("saindo do programa\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    }while(opt!=0);

    for(int i=0; i<total; i++){
        printf("\nPessoa %i\nNome: %s\nIdade: %i\n", i+1, listaPessoa[i]->nome, listaPessoa[i]->idade);
    }

    for(int i=0; i<total; i++){
        free(listaPessoa[i]);
    }
    free(listaPessoa);
    listaPessoa=NULL;

    return 0;
}

void limparBuffer(){
    int c;
    while((c=getchar())!='\n' && c!=EOF){}
}

void adicionarPessoa(Pessoa** listaPessoa, int* total, int* capacidade){
    int opt;
    do{    
        if((*total)<(*capacidade)){
            Pessoa* p = malloc(sizeof(Pessoa));

            if(p==NULL){
                printf("erro ao alocar memoria\n");
                return;
            }
            listaPessoa[*total]=p;

            printf("Insira o nome: \n");
            scanf(" %s", (listaPessoa)[*total]->nome);
            limparBuffer();

            printf("Insira a idade:\n");
            scanf(" %i", &(listaPessoa)[*total]->idade);
            limparBuffer();

            (*total)++;
        }
        else
            printf("Armazenamento lotado\nOtimize a memoria do programa!\n");

        printf("deseja cadastrar outra pessoa?\n sim[1] nao[0]\n");
        scanf(" %i", &opt);
    }while(opt==1);

}

void otimizarMemoria(Pessoa*** listaPessoa, int total, int* capacidade){
    int novaCapacidade;

    if(total<(*capacidade)){
        novaCapacidade = total;
        Pessoa** tempLista = realloc(*listaPessoa, sizeof(Pessoa*)*novaCapacidade);
        if(tempLista==NULL){
            printf("Erro ao otimizar memoria\n");
            return;
        }

        printf("memoria otimizada\n");
        (*capacidade)=novaCapacidade;

        *listaPessoa = tempLista;

    }

    else{
        novaCapacidade = (*capacidade) + 3;
        Pessoa** tempLista = realloc(*listaPessoa, sizeof(Pessoa*)*novaCapacidade);
        if(tempLista==NULL){
            printf("Erro ao otimizar memoria\n");
            return;
        }
        printf("memoria otimizada\n");
        (*capacidade)=novaCapacidade;
        *listaPessoa = tempLista;
    }

}

