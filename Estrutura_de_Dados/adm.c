#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Pessoa{
    char nome[21];
    char cpf[12];
    int idade;
    char sexo;
    char telefone[12];
}Pessoa;

int alocar(int *capacidade, Pessoa **ptr);

int desalocar(int *capacidade, Pessoa **ptr, int novaCapacidade);

void limparBuffer();

void cadastrarPessoa(Pessoa **ptr, int *capacidade, int *totalPessoas);

void alterarPessoas(Pessoa *ptr, int totalPessoas);

int busca(Pessoa *buscaPtr, char tempString[12], int totalPessoas);

void removerPessoas(Pessoa **ptr, int *totalPessoas, int *capacidade);

void mostrarPessoa(Pessoa *ptr, int i);

void exibirUmRegistro(Pessoa *ptr, int totalPessoas);

void exibirTodosRegistros(Pessoa *ptr, int totalPessoas);

int main(void){
    Pessoa *cadastroP=NULL;
    cadastroP = realloc(NULL, sizeof(Pessoa)*1);
    int capacidade  = 1;
    int totalPessoas = 0;

    if(cadastroP==NULL){
        printf("erro ao alocar memoria\n");
        exit(1);
    }
    int opt=0;
    printf(">> CADASTRO DE PESSOAS <<\n");
    do{
        printf("cadastrar pessoa ------ 1\n");
        printf("remover uma pesosa ---- 2\n");
        printf("alterar registro ------ 3\n");
        printf("exibir registro unico - 4\n");
        printf("exibir todos ---------- 5\n");
        printf("sair do programa ------ 0\n");
        scanf(" %i", &opt);

        switch (opt){
            case 1:
            cadastrarPessoa(&cadastroP, &capacidade, &totalPessoas);
                break;
            case 2:
                removerPessoas(&cadastroP, &totalPessoas, &capacidade);
                break;
            case 3:
                alterarPessoas(cadastroP, totalPessoas);
                break;
            case 4:
                exibirUmRegistro(cadastroP, totalPessoas);
                break;
            case 5:
                exibirTodosRegistros(cadastroP, totalPessoas);
                break;
            case 0:
                break;
            default:
                printf("insira uma opcao valida\n");
    
        }
    }while(opt!=0);

    free(cadastroP);
    cadastroP = NULL;

    return 0;
}
int alocar(int *capacidade, Pessoa **ptr){
    int novaCapacidade = (*capacidade) + 3;
        
    Pessoa *tempPtr = realloc(*ptr, sizeof(Pessoa)*novaCapacidade);
    if(tempPtr==NULL){
        printf("\nerro ao alocar memoria\n");
        return 1;
    }
    *ptr = tempPtr;

    (*capacidade) = novaCapacidade;
    printf("\nalocacao feita com sucesso\n");

    return 0;
}

int desalocar(int *capacidade, Pessoa **ptr, int novaCapacidade){
    if (novaCapacidade <= 0) {
        printf("\nCapacidade final 0. Liberando toda a memoria.\n");
        free(*ptr);
        *ptr = NULL;
        *capacidade = 0;
        return 0;
    }
    Pessoa *tempPtr = realloc(*ptr, sizeof(Pessoa)*novaCapacidade);
    if(tempPtr==NULL){
        printf("\nerro ao realocar memoria\n");
        return 1;
    }
    *ptr = tempPtr;
    (*capacidade) = novaCapacidade;
    printf("\nrealocacao feita com sucesso\n");
    return 0;
}

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

void cadastrarPessoa(Pessoa **ptr, int *capacidade, int *totalPessoas){
    char tempC;
    do{
        if(*totalPessoas==*capacidade){
            int teste = alocar(capacidade, ptr);
            if(teste)
                break;
        }

        int i = *totalPessoas;

        printf("\ninsira o nome da Pessoa: ");
        scanf(" %20s", (*ptr)[i].nome);
        limparBuffer();

        printf("\ninsira o cpf da pessoa: ");
        scanf(" %11s", (*ptr)[i].cpf);
        limparBuffer();

        printf("\ninsira a idade da pessoa: ");
        scanf(" %i", &(*ptr)[i].idade);
        limparBuffer();

        printf("\ninsira o sexo da pessoa\n[F] Feminino\n[M] Masculino\n");
        
        scanf(" %c", &tempC);
        limparBuffer();

        if(tolower(tempC)=='f' || tolower(tempC)=='m')
            (*ptr)[i].sexo = tempC;
        else {
            printf("\nOpcao invalida, valor nao cadastrado");
            (*ptr)[i].sexo = '?';
        }
            

        printf("\ninsira o telefone da pessoa: ");
        scanf(" %11s", (*ptr)[i].telefone);
        limparBuffer();

        (*totalPessoas)++;

        printf("\ndeseja cadastrar outra pessoa?\n s - sim\n n - nao\n");
        scanf(" %c", &tempC);

    }while(tolower(tempC)=='s');
      if(*totalPessoas < *capacidade){
        desalocar(capacidade, ptr, *totalPessoas);
      }
    
}

void alterarPessoas(Pessoa *ptr, int totalPessoas){
    char tempS[12];
    printf("\ninsira o cpf da pessoa que deseja alterar:\n");
    scanf(" %s", tempS);

    int i = busca(ptr, tempS, totalPessoas);

    if(i!=-1){
        printf("\ninsira o nome da Pessoa: ");
        scanf(" %s", ptr[i].nome);
        limparBuffer();

        printf("\ninsira o cpf da pessoa: ");
        scanf(" %s", ptr[i].cpf);
        limparBuffer();

        printf("\ninsira a idade da pessoa: ");
        scanf(" %i", &ptr[i].idade);
        limparBuffer();

        printf("\ninsira o sexo da pessoa\n[F] Feminino\n[M] Masculino\n");
        char tempC;
        scanf(" %c", &tempC);
        limparBuffer();

        if(tolower(tempC)=='f' || tolower(tempC)=='m')
            ptr[i].sexo = tempC;
        else 
            printf("\nOpcao invalida, valor nao cadastrado");

        printf("\ninsira o telefone da pessoa: ");
        scanf(" %s", ptr[i].telefone);
        limparBuffer();
    }
    else
        printf("\ncpf não esta cadastrado no sistema\n");
     
}

int busca(Pessoa *buscaPtr, char tempString[12], int totalPessoas){
    for(int i=0; i<totalPessoas; i++){
        if(strcmp(tempString, buscaPtr[i].cpf)==0)
            return i;
    }
    return -1;
}

void removerPessoas(Pessoa **ptr, int *totalPessoas, int *capacidade){
    if(*totalPessoas==0){
        printf("nao ha pessoas para remover\n");
        return;
    }

    char tempS[12];
    printf("\ninsira o cpf da pessoa que deseja remover:\n");
    scanf(" %11s", tempS);

    int i = busca(*ptr, tempS, *totalPessoas);
    
    
    if(i!=-1){
        for(int j = i; j<(*totalPessoas)-1; j++){
            (*ptr)[j]=(*ptr)[j+1];
        }
        printf("\nregistro removido\n");
        (*totalPessoas)--;

        if((*capacidade) - (*totalPessoas) > 5){
            desalocar(capacidade, ptr, *totalPessoas);
        }
    }
    else{
        printf("\nfalha ao remover o registro\n");
    }
}

void mostrarPessoa(Pessoa *ptr, int i){
    printf("\n -> PESSOA %i\n", i+1);
    printf("Nome: %s\n", ptr[i].nome);
    printf("CPF: %s\n", ptr[i].cpf);
    printf("Idade: %i\n", ptr[i].idade);
    printf("Sexo: %c\n", ptr[i].sexo);
    printf("Telefone: %s\n", ptr[i].telefone);
}

void exibirUmRegistro(Pessoa *ptr, int totalPessoas){
    char tempS[12];
    printf("\ninsira o cpf da pessoa que deseja alterar:\n");
    scanf(" %11s", tempS);
    limparBuffer();

    int i = busca(ptr, tempS, totalPessoas);
    if(i!=-1){
        mostrarPessoa(ptr, i);
    }
    else
        printf("cpf nao encontrado no sistema\n");
    
}

void exibirTodosRegistros(Pessoa *ptr, int totalPessoas){
    for(int i = 0; i<totalPessoas; i++){
        mostrarPessoa(ptr, i);
    }
}