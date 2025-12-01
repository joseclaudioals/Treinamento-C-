//nao finalizado
#include <stdio.h>
#include <stdlib.h>

typedef struct Caixa{
    int id;
    int tamanho; //podendo ser apenas 1, 2 ou 3
    int status; //onde 0 é aguardando e 1 é empilhado
}Caixa;

typedef struct Fila{
    Caixa caixas[3];
    int inicio;
    int fim;
    int total;
}Fila;

typedef struct Pilha{
    Caixa caixas[3];
    int topo;
    int qntItens;
}Pilha;

// -- funções fila --
void iniciarFila(Fila* f);
void inserirCaixa(Fila* fila);
void removerCaixa(Fila* fila);

//-- funções gerais --

int busca(int id, Caixa* caixas, int n);

//-- funções pilha --
void iniciarPilha(Pilha* p);
void push(Pilha* p, Caixa c);
int ordenarPilha(Caixa* caixas, int qntItens);


int main(void){
    Fila f;
    iniciarFila(&f);
    Pilha p1, p2;
    iniciarPilha(&p1);
    iniciarPilha(&p2);
    int opt;
    do{
        printf("Inserir caixa -- 1\n");
        printf("Remover caixa -- 2\n");
        printf("Empilhar ------- 3\n");
        printf("Desempilhar ---- 4\n");
        printf("Sair ----------- 0\n");
        scanf(" %i", &opt);
        
        switch(opt){
            case 1:
                inserirCaixa(&f);
                break;
            case 2:
                removerCaixa(&f);
                break;
            case 3:
                //empilhar();
                break;
            case 4:
                printf("Qual pilha irá desempilhar?");
                scanf(" %i", &opt);
                switch(opt){
                    case 1:
                        break;
                    case 2:
                        break;
                }
                //desempilhar();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida\n");
        }
    }while(opt!=0);
    
    return 0;
}

// -- funções fila --
void iniciarFila(Fila* f){
    f->inicio=0;
    f->fim=-1;
    f->total=0;
}

void inserirCaixa(Fila* fila){
    if(fila->total < sizeof(fila->caixas)/sizeof(Caixa)){
        Caixa c;
        printf("Insira o id:\n");
        scanf(" %i", &c.id);
        printf("Insira o tamanho da caixa:\n");
        scanf(" %i", &c.tamanho);
        c.status = 0;
        
        if(c.tamanho==3){
            push();
            return;
        }
        
        fila->caixas[fila->fim+1]=c;
        fila->fim=fila->total;
        fila->fim++;
        
        return;
    }
    printf("Fila de espera lotada\n");
}

void removerCaixa(Fila* fila){
    int idbusca;
    printf("Insira o id da caixa a ser removida\n");
    scanf(" %i", &idbusca);
    
    int i = busca(idbusca, fila->caixas, fila->total);
    
    if(i>=0){
        for(int j=i; j<fila->total-1; j++){
            fila->caixas[j]=fila->caixas[j+1];
        }
        fila->total--;  
        printf("caixa removida\n");
        return;
    }
    printf("Caixa nao encontrada\n");
}

//-- funções gerais --

int busca(int id, Caixa* caixas, int n){
    for(int i=0; i<n;i++){
        if(id==caixas[i].id){
            return i;
        }
    }
    return -1;
}

//-- funções pilha --
void iniciarPilha(Pilha* p){
    p->topo=-1;
}

void push(Pilha* p, Caixa* c){
    if(p->qntItens==3){
        printf("Pilha cheia\n");
        return;
    }
    p->topo++;
    p->caixas[p->topo]=c;
    printf("valor inserido na pilha;");
}

void ordenarPilha(Caixa* caixas, int qntItens){
    if(qntItens==1){
        printf("Pilha ordenada\n");
        return;
    }
    for(int i=1; i<qntItens; i++){
        Caixa key = caixas[i];
        int j = i-1;
        
        while(key<caixas[j]&&j>=0){
            caixas[j+1]=caixas[j];
            j-=1;
        }
        caixas[j+1]=key;
    }
    printf("pilha ordenada\n");
}