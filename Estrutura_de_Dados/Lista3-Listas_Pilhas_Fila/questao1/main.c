//considerarei o usuário inteligente
// no caso nao irá digitar letras na string

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    float valor;
    struct node* proximo;
}node;

typedef struct pilha{
    struct node* topo;
    int qnt;
}pilha;

void push(float valor, pilha* p);
float pop(pilha* p);
void liberarPilha(pilha* p);
int tokenisOperando(char* tokens);
void limparBuffer();

int main(void){
    char str[20];

    pilha p;
    p.topo = NULL;
    p.qnt = 0;

    // recebendo digitos

    printf("digite a expressao:");
    scanf(" %[^\n]", str);

    limparBuffer();

    char* tokens = strtok(str, " ");

    while(tokens != NULL){

        if(!tokenisOperando(tokens)){
            float valor = strtof(tokens, NULL);
            push(valor, &p);
        }
        else{
            if(p.qnt == 1){
                printf("operacao invalida, numero restante sem operando\n");
                pop(&p);
                break;
            }
            if(!(strcmp(tokens, "+")) && p.qnt==2){
                float valor2 = pop(&p);
                float valor1 = pop(&p);

                float resultado = valor1 + valor2;
                push(resultado, &p);
            }
            else if(!(strcmp(tokens, "-")) && p.qnt==2){
                float valor2 = pop(&p);
                float valor1 = pop(&p);

                float resultado = valor1 - valor2;
                push(resultado, &p);
            }
            else if(!(strcmp(tokens, "*")) && p.qnt==2){
                float valor2 = pop(&p);
                float valor1 = pop(&p);

                float resultado = valor1 * valor2;
                push(resultado, &p);
            }
            else if(!(strcmp(tokens, "/")) && p.qnt==2){
                float valor2 = pop(&p);
                //validando se a divisao será por 0
                if(valor2==0){
                    printf("divisao por 0 invalida\n");
                    break;
                }
                float valor1 = pop(&p);

                float resultado = valor1 / valor2;
                push(resultado, &p);
            }
            else{
                printf("letra inserida no comando\n");
                break;
            }
        
        }
        tokens = strtok(NULL, " ");

    }

    if(p.qnt==1)
        printf("Resultado: %.2f\n", pop(&p));

    liberarPilha(&p);
    printf("Programa encerrado");
    
    return 0;
}

void push(float valor, pilha* p){
    node* n = malloc(sizeof(node));

    if(n==NULL){
        printf("erro ao alocar token na pilha\n");
        exit(1);
    }

    n->valor=valor;
    n->proximo = p->topo;
    p->topo = n;

    p->qnt++;
}

float pop(pilha* p){
    if(p->topo==NULL){
        printf("pilha vazia");
        return 0;
    }

    node* temp = p->topo;
    p->topo = temp->proximo;
    float valor = temp->valor;
    free(temp);
    p->qnt--;

    return valor;
}

void liberarPilha(pilha* p){
    node* temp = p->topo;

    while(temp!=NULL){
        node* aux = temp;
        temp = temp->proximo;
        free(aux);
    }

    p->qnt=0;
}

int tokenisOperando(char* tokens){
    if(!(strcmp(tokens, "+"))||!(strcmp(tokens, "-"))||!(strcmp(tokens, "*"))||!(strcmp(tokens, "/")))
        return 1;

    return 0;
}

void limparBuffer(){
    char c;
    while((c=getchar())!='\n' && c!=EOF){}
}