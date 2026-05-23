#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{
    char c;
    struct node* proximo;
}node;

typedef struct fila{
    node* inicio;
    node* fim;
}fila;

typedef struct pilha{
    node* topo;
}pilha;

void limparStr(char* str);
void push(char str[32], pilha* p);
char pop(pilha* p);
void enqueue(char str[32], fila* f);
char dequeue(fila* f);
int ehPalindromo(fila* f, pilha* p, char str[32]);

int main(void){
    fila f;
    f.inicio = NULL;
    f.fim = NULL;

    pilha p;
    p.topo = NULL;

    char str[32];

    printf("insira uma frase");
    scanf(" %[^\n]", str);

    limparStr(str);
    printf("%s\n", str);

    push(str, &p);
    enqueue(str, &f);

    if(ehPalindromo(&f, &p, str))
        printf("eh palindromo >:D\n");
        else
            printf("nao eh palindromo T^T\n");

    return 0;
}

void limparStr(char* str){
    int i=0;
    int j=0;

    while(str[i]!='\0'){
        if(str[i]!=' '){
            str[j]=str[i];
            j++;
        }
        i++;
    }
    str[j]='\0';

    i = 0;
    while(str[i]!='\0'){
        str[i] = tolower(str[i]);
        i++;
    }
}

void push(char str[32], pilha* p){
    int i = 0;
    while(str[i]!='\0'){
        node* n = malloc(sizeof(node));

        if(n==NULL){
            printf("erro ao alocar memoria\n");
            return;
        }

        n->c=str[i];

        n->proximo=p->topo;
        p->topo=n;
        i++;
    }
}

char pop(pilha* p){
    char c = p->topo->c;

    node* temp = p->topo;
    p->topo = temp->proximo;

    free(temp);

    return c;
    
}

void enqueue(char str[32], fila* f){
    int i=0;
    while(str[i]!='\0'){
        node* n = malloc(sizeof(node));

        if(n==NULL){
            printf("erro ao alocar memoriaabababa\n");
            return;
        }

        n->c=str[i];
        n->proximo = NULL;

        if(f->inicio==NULL){
            f->inicio=n;
            f->fim=n;
        }
        else{
            f->fim->proximo=n;
            f->fim=n;
        }

        i++;
    }
}

char dequeue(fila* f){
    char c = f->inicio->c;

    node* temp = f->inicio;
    f->inicio = temp->proximo;
    free(temp);

    return c;
}

int ehPalindromo(fila* f, pilha* p, char str[32]){
    int i=0;
    while(str[i]!='\0'){
        if(pop(p) != dequeue(f))
            return 0;

        i++;
    }
    return 1;
}

