#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct noPessoa{
    char nome[21];
    char cpf[12];
    int idade;
    char sexo;
    char telefone[12];
    
    struct noPessoa *proximo;
}noPessoa;

noPessoa *head = NULL;
int totalPessoas=0;

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

void cadastrarPessoa(){
    char tempC;
    do{
        noPessoa *novoNode = malloc(sizeof(noPessoa));
        if(novoNode==NULL){
        printf("erro catastrofico\n");
        exit(1);
        }
        printf("\ninsira o nome da Pessoa: ");
        scanf(" %20s", novoNode->nome);
        limparBuffer();

        printf("\ninsira o cpf da pessoa: ");
        scanf(" %11s", novoNode->cpf);
        limparBuffer();

        printf("\ninsira a idade da pessoa: ");
        scanf(" %i", &novoNode->idade);
        limparBuffer();

        printf("\ninsira o sexo da pessoa\n[F] Feminino\n[M] Masculino\n");
        
        scanf(" %c", &tempC);
        limparBuffer();

        if(tolower(tempC)=='f' || tolower(tempC)=='m')
            novoNode->sexo = tempC;
        else {
            printf("\nOpcao invalida, valor nao cadastrado");
            novoNode->sexo = '?';
        }
            
        totalPessoas++;
        novoNode->proximo=NULL; // o novo nó sempre será o ultimo
            
        if(head==NULL)
            head = novoNode;
        else{
            noPessoa *ultimo = head;
            while(ultimo->proximo != NULL)
                ultimo = ultimo->proximo;
                
            ultimo->proximo=novoNode;
        }
        
        printf("\ndeseja cadastrar outra pessoa?\n s - sim\n n - nao\n");
        scanf(" %c", &tempC);

    }while(tolower(tempC)=='s');
}

void removerCadastro(){
    if(head==NULL){
        printf("lista vazia, nada a remover. \n");
        return;
    }
}

int buscar(char cpf[12]){
    int con=1;
    noPessoa *noAtual = head;
    while(noAtual!=NULL){
        if(strcmp(cpf, *noAtual->cpf)==0)
            return con;
        noAtual = noAtual->proximo;
    }
}

int main(void){
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
                //removerPessoas();
                break;
            case 3:
                //alterarPessoas();
                break;
            case 4:
                //exibirUmRegistro();
                break;
            case 5:
                //exibirTodosRegistros();
                break;
            case 0:
                break;
            default:
                printf("insira uma opcao valida\n");
    
        }
    }while(opt!=0);
}