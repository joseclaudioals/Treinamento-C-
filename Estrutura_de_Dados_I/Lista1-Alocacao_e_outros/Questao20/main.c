#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14

typedef struct Circulo{
    float raio;
}Circulo;

typedef struct Quadrado{
    float lado;
}Quadrado;

typedef struct Forma{
    int tipo; //1 quadrado - 2 circulo
    void *dados;
    float (*calcularArea)(void *dados);
}Forma;

float areaCirculo(void* forma);
float areaQuadrado(void* forma);
void cadastroForma(Forma** lista, int qnt);
void liberarMemoria(Forma*** lista, int qnt);

int main(void){
    int qnt;
    printf("quantas formas o array deve ter?\n");
    scanf(" %i", &qnt);
    
    Forma** lista=malloc(sizeof(Forma*)*qnt);
    
    cadastroForma(lista, qnt);
    
    for(int i = 0; i<qnt; i++){
        printf("Area %s: %.2f\n", lista[i]->tipo==1 ? "quadrado" : "circulo", lista[i]->calcularArea(lista[i]->dados));
    }
    
    liberarMemoria(&lista, qnt);
    
    return 0;
}

float areaCirculo(void* forma){
    Circulo* c = (Circulo*)forma;
    
    return PI * pow(c->raio, 2);
}
float areaQuadrado(void* forma){
    Quadrado* q = (Quadrado*)forma;
    
    return pow(q->lado, 2);
}

void cadastroForma(Forma** lista, int qnt){
    for(int i=0; i<qnt; i++){
        int opt;
        
        lista[i]=malloc(sizeof(Forma));
        
        printf("qual forma deseja cadastrar?\n");
        printf("quadrado [1] circulo [2]");
        scanf(" %i", &opt);
        switch(opt){
            case 1:
                Quadrado* q = malloc(sizeof(Quadrado));
                printf("lado: ");
                scanf(" %f", &q->lado);
                lista[i]->tipo = 1;
                lista[i]->dados = q;
                lista[i]->calcularArea=areaQuadrado;
                break;
            case 2:
                Circulo* c = malloc(sizeof(Circulo));
                printf("raio: ");
                scanf(" %f", &c->raio);
                lista[i]->tipo = 2;
                lista[i]->dados = c;
                lista[i]->calcularArea=areaCirculo;
                break;
        }
        printf("forma cadastrada\n");
    }
}

void liberarMemoria(Forma*** lista, int qnt){
    for(int i=0; i<qnt; i++){
        free((*lista)[i]->dados);
        free((*lista)[i]);
    }
    free((*lista));
    *lista=NULL;
    printf("memoria liberada\n");
}

