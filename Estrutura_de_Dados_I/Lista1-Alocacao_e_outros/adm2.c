/* 
   este programa tem o mesmo objetivo que adm.c 
   mas irá usar array de ponteiros para structs
   ao invés de array de structs

   tambem irei fazer o array e as suas variáveis de controle
   globais, para facilitar.
*/

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

//usar variaveis e vetores globais facilita muito na escrita do codigo
//pois despensa a preocupação em relação aos parametros e argumentos de uma função
//assim, tambem economizamos memoria por não precisarmos de variaveis
//ou ponteiroa adicionais para realizar as operações 

Pessoa **cadastroP=NULL;
int capacidade  = 0;
int totalPessoas = 0;

int alocar();
int desalocar();
void limparBuffer();
void cadastrarPessoa();
void alterarPessoas();
int busca(char tempString[12]);
void removerPessoas();
void mostrarPessoa(int i);
void exibirUmRegistro();
void exibirTodosRegistros();

int main(void){
    cadastroP = realloc(NULL, sizeof(Pessoa *)*1);
    capacidade = 1;
    if(cadastroP==NULL){
        printf("erro ao alocar memoria\n");
        exit(1);
    }

    cadastroP[0]=NULL;

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
            cadastrarPessoa();
                break;
            case 2:
                removerPessoas();
                break;
            case 3:
                alterarPessoas();
                break;
            case 4:
                exibirUmRegistro();
                break;
            case 5:
                exibirTodosRegistros();
                break;
            case 0:
                break;
            default:
                printf("insira uma opcao valida\n");
    
        }
    }while(opt!=0);

    for(int i=0; i<totalPessoas; i++){
        free(cadastroP[i]);
    }

    free(cadastroP);
    cadastroP = NULL;

    return 0;
}

int alocar(){
    int novaCapacidade = capacidade + 3;
        
    Pessoa **tempPtr = realloc(cadastroP, sizeof(Pessoa *)*novaCapacidade);
    if(tempPtr==NULL){
        printf("\nerro ao alocar memoria\n");
        return 1;
    }
    cadastroP = tempPtr;
    for(int i = capacidade; i<novaCapacidade; i++){
        cadastroP[i]=NULL;
    }
    capacidade = novaCapacidade;
    printf("\nalocacao feita com sucesso\n");

    return 0;
}

int desalocar(){
    if (totalPessoas <= 0) {
        printf("\nCapacidade final 0. Liberando toda a memoria.\n");
        free(cadastroP);
        cadastroP = NULL;
        capacidade = 0;
        return 0;
    }
    Pessoa **tempPtr = realloc(cadastroP, sizeof(Pessoa *)*totalPessoas);
    if(tempPtr==NULL){
        printf("\nerro ao realocar memoria\n");
        return 1;
    }
    cadastroP = tempPtr;
    (capacidade) = totalPessoas;
    printf("\nrealocacao feita com sucesso\n");
    return 0;
}

void cadastrarPessoa(){
    char tempC;
    do{
        if(totalPessoas==capacidade){
            int teste = alocar();
            if(teste)
                break;
        }

        cadastroP[totalPessoas] = realloc(NULL, sizeof(Pessoa)); // precisamos alocar o tamanho de bytes de pessoas para o ponteiro no vetor 

        if(cadastroP[totalPessoas]==NULL){
            printf("erro catastrofico\n");
            break;
        }

        printf("\ninsira o nome da Pessoa: ");
        scanf(" %20s", cadastroP[totalPessoas]->nome);
        limparBuffer();

        printf("\ninsira o cpf da pessoa: ");
        scanf(" %11s", cadastroP[totalPessoas]->cpf);
        limparBuffer();

        printf("\ninsira a idade da pessoa: ");
        scanf(" %i", &cadastroP[totalPessoas]->idade);
        limparBuffer();

        printf("\ninsira o sexo da pessoa\n[F] Feminino\n[M] Masculino\n");
        
        scanf(" %c", &tempC);
        limparBuffer();

        if(tolower(tempC)=='f' || tolower(tempC)=='m')
            cadastroP[totalPessoas]->sexo = tempC;
        else {
            printf("\nOpcao invalida, valor nao cadastrado");
            cadastroP[totalPessoas]->sexo = '?';
        }
            

        printf("\ninsira o telefone da pessoa: ");
        scanf(" %11s", cadastroP[totalPessoas]->telefone);
        limparBuffer();

        totalPessoas++;

        printf("\ndeseja cadastrar outra pessoa?\n s - sim\n n - nao\n");
        scanf(" %c", &tempC);

    }while(tolower(tempC)=='s');
      if(totalPessoas < capacidade){
        desalocar();
      }
    
}

void alterarPessoas(){
    char tempS[12];
    printf("\ninsira o cpf da pessoa que deseja alterar:\n");
    scanf(" %s", tempS);
    limparBuffer();

    int i = busca(tempS);

    if(i!=-1){
        printf("\ninsira o nome da Pessoa: ");
        scanf(" %s", cadastroP[i]->nome);
        limparBuffer();

        printf("\ninsira o cpf da pessoa: ");
        scanf(" %s", cadastroP[i]->cpf);
        limparBuffer();

        printf("\ninsira a idade da pessoa: ");
        scanf(" %i", &cadastroP[i]->idade);
        limparBuffer();

        printf("\ninsira o sexo da pessoa\n[F] Feminino\n[M] Masculino\n");
        char tempC;
        scanf(" %c", &tempC);
        limparBuffer();

        if(tolower(tempC)=='f' || tolower(tempC)=='m')
            cadastroP[i]->sexo = tempC;
        else 
            printf("\nOpcao invalida, valor nao cadastrado");

        printf("\ninsira o telefone da pessoa: ");
        scanf(" %s", cadastroP[i]->telefone);
        limparBuffer();
    }
    else
        printf("\ncpf não esta cadastrado no sistema\n");
     
}

int busca(char tempString[12]){
    for(int i=0; i<totalPessoas; i++){
        if(strcmp(tempString, cadastroP[i]->cpf)==0)
            return i;
    }
    return -1;
}

void removerPessoas(){
    if(totalPessoas==0){
        printf("nao ha pessoas para remover\n");
        return;
    }

    char tempS[12];
    printf("\ninsira o cpf da pessoa que deseja remover:\n");
    scanf(" %11s", tempS);

    int i = busca(tempS);
    
    if(i!=-1){
        free(cadastroP[i]);
        for(int j = i; j<totalPessoas-1; j++){
            cadastroP[j]=cadastroP[j+1];
        }
        printf("\nregistro removido\n");
        totalPessoas--;

        if(capacidade - totalPessoas > 5){
            desalocar();
        }
    }
    else{
        printf("\nfalha ao remover o registro\n");
    }
}

void mostrarPessoa(int i){
    printf("\n -> PESSOA %i\n", i+1);
    printf("Nome: %s\n", cadastroP[i]->nome);
    printf("CPF: %s\n", cadastroP[i]->cpf);
    printf("Idade: %i\n", cadastroP[i]->idade);
    printf("Sexo: %c\n", cadastroP[i]->sexo);
    printf("Telefone: %s\n", cadastroP[i]->telefone);
}

void exibirUmRegistro(){
    char tempS[12];
    printf("\ninsira o cpf da pessoa que deseja alterar:\n");
    scanf(" %11s", tempS);
    limparBuffer();

    int i = busca(tempS);
    if(i!=-1){
        mostrarPessoa(i);
    }
    else
        printf("cpf nao encontrado no sistema\n");
    
}

void exibirTodosRegistros(){
    for(int i = 0; i<totalPessoas; i++){
        mostrarPessoa(i);
    }
}

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}