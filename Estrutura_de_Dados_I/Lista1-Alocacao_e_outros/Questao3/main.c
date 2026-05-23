#include <stdio.h>
#include <stdlib.h>

typedef struct Ponto{
    int x;
    int y;
}Ponto;

Ponto* criarPonto(int x, int y);

int main(void){
    Ponto* p1 = criarPonto(10, 5);
    printf("Ponto x: %i\nPonto y: %i", p1->x, p1->y);

    free(p1);
    p1 = NULL;
    return 0;
}

Ponto* criarPonto(int x, int y){
    Ponto* pontoX = malloc(sizeof(Ponto));

    if(pontoX==NULL){
        printf("Falha catastrofica! Erro ao alocar\n");
        exit(1);
    }

    pontoX->x = x;
    pontoX->y = y;

    return pontoX;
}