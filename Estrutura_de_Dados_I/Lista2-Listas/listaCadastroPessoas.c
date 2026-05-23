#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct noPessoa{
    char nome[21];
    char cpf[12];
    int idade;
    char sexo;
    char telefone[12];
    
    struct noPessoa *proximo;
}noPessoa;

noPessoa *head = NULL; 

void limparBuffer();
void cadastrarPessoa();
void inputInformacao();
int controleRepetir();
void removerCadastro();
int buscar(char cpf[12]);
void imprimir(noPessoa* node);
void exibirUmRegistro();
void exibirTodosRegistros();
void alterarPessoas();


int main(void){
    int opt=0;
    printf(">> CADASTRO DE PESSOAS <<\n");
    do{
        printf("cadastrar pessoa ------ 1\n");
        printf("remover um cadastro ---- 2\n");
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
                removerCadastro();
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

    noPessoa* atual = head;
    while(atual!=NULL){
        noPessoa* temp= atual->proximo;
        free(atual);
        atual = temp;
    }
    head = NULL;
}

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}
void cadastrarPessoa(){
    do{
        noPessoa *novoNode = malloc(sizeof(noPessoa));
        if(novoNode==NULL){
            printf("falha catastrofica, erro ao alocar memoria!\b");
            return;
        }
        printf("node criado com sucesso\n");

        inputInformacao(novoNode);

        novoNode->proximo=NULL; //node inserido é sempre o ultimo

        //verificando se a lista esta vazia
        if(head==NULL){
            head=novoNode;
        }
        else{
            noPessoa *ultimo = head;
            while(ultimo->proximo!=NULL){
                ultimo=ultimo->proximo;
            }
            ultimo->proximo=novoNode;
        }
        
    }while(controleRepetir());
}
void inputInformacao(noPessoa *novoNode){
    printf(">>> Cadastro Pessoa <<<\n");
    printf("Insira o nome:\n");
    scanf(" %20[^\n]", novoNode->nome);
    limparBuffer();

    printf("Insira o CPF\n");
    scanf(" %s", novoNode->cpf);
    limparBuffer();

    printf("Insira a idade:\n");
    scanf(" %i", &novoNode->idade);
    limparBuffer();

    printf("Insira Nº de telefone:\n");
    scanf(" %s", novoNode->telefone);
    limparBuffer();

    char tempC;
    printf("Insira o sexo:\n");
    printf("Masculino [M]\n");
    printf("Feminino [F]\n");
    scanf(" %c", &tempC);
    limparBuffer();

    if(tolower(tempC)=='f'||tolower(tempC)=='m')
        novoNode->sexo = tolower(tempC);
        else{
            printf("opcao invalida, sexo nao cadastrado!\n");
            novoNode->sexo=' ';
        }
}
void imprimir(noPessoa* node){
    printf(">>CADASTROS<<\n");
    printf("Nome: %s\n", node->nome);
    printf("CPF: %s\n", node->cpf);
    printf("Idade: %i\n", node->idade);
    printf("Telefone: %s\n", node->telefone);
    printf("Sexo: %c\n", toupper(node->sexo));

}
int controleRepetir(){
    char tempC;
    do{
        printf("deseja repetir a operacao?\n");
        printf("SIM[s] | NAO[n]\n");
        scanf(" %c", &tempC);
        limparBuffer();
        if(!(tolower(tempC)=='s'||tolower(tempC)=='n'))
            printf("opcao invalido, digite novamente!\n");

        if(tolower(tempC)=='s')
            return 1;
        if(tolower(tempC)=='n')
            return 0;
    }while(!(tolower(tempC)=='s'||tolower(tempC)=='n'));

    return 0;
}
void removerCadastro(){
    char cpf[12];
    printf("insira o CPF da pessoa que deseja remover os dados\n");
    scanf(" %s", cpf);
    limparBuffer();

    if(head==NULL){
        printf("lista vazia, nada a remover. \n");
        return;
    }
   noPessoa* nodeAtual = head;
   noPessoa* nodeAnterior = NULL;

   while(nodeAtual!=NULL && strcmp(nodeAtual->cpf, cpf)!=0){
    nodeAnterior = nodeAtual;
    nodeAtual = nodeAtual->proximo;
   }

   if(nodeAtual==NULL){
    printf("CPF nao encontrado!\n");
    return;
   }

   if(nodeAtual==head){
    head=nodeAtual->proximo;
   }
   else{   
    nodeAnterior->proximo=nodeAtual->proximo;
    }
    printf("Removendo Cadasro de: %s\n", nodeAtual->nome);
    free(nodeAtual);
 
}
void exibirUmRegistro(){
    char cpf[12];
    printf("insira o CPF da pessoa que deseja imprimir os dados\n");
    scanf(" %s", cpf);
    limparBuffer();

    noPessoa* nodeRequerido = head;
    if(nodeRequerido==NULL){
        printf("Lista de cadastro vazia\n");
        return;
    }
    while(nodeRequerido!=NULL){
        if(strcmp(nodeRequerido->cpf, cpf)==0){
            imprimir(nodeRequerido);
            return;
        }
        nodeRequerido = nodeRequerido->proximo;
    }
    printf("Pessoa procurada nao esta cadastrada!\n");
}
void exibirTodosRegistros(){
    noPessoa* nodeRequerido = head;
    if(nodeRequerido==NULL){
        printf("Lista de cadastro vazia\n");
        return;
    }
    while(nodeRequerido!=NULL){
        imprimir(nodeRequerido);
        nodeRequerido = nodeRequerido->proximo;
    }
}
void alterarPessoas(){
    char cpf[12];
    printf("insira o CPF da pessoa que deseja imprimir os dados\n");
    scanf(" %s", cpf);
    limparBuffer();

    noPessoa* nodeRequerido = head;
    if(nodeRequerido==NULL){
        printf("Lista de cadastro vazia\n");
        return;
    }
    while(nodeRequerido!=NULL){
        if(strcmp(nodeRequerido->cpf, cpf)==0){
            inputInformacao(nodeRequerido);
            return;
        }
        nodeRequerido = nodeRequerido->proximo;
    }
    printf("Pessoa procurada nao esta cadastrada!\n");

}