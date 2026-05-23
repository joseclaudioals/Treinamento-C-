#include <stdio.h>
#include <stdlib.h>

void liberarMemoria(int** matriz, int l);

int main(void){
    int linhas, colunas;

    printf("Matriz dinamica\n");
    printf("insira a quantidade de colunas:\n");
    scanf(" %i", &colunas);
    printf("insira a quantidade de linhas\n");
    scanf(" %i", &linhas);

    int **matriz = malloc(linhas*sizeof(int*));
    for(int i=0; i<linhas; i++){
        matriz[i]=malloc(colunas*sizeof(int));
    }
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            matriz[i][j] = i+j;
        }
    }

    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%i ", matriz[i][j]);
        }
        printf("\n");
    }

    liberarMemoria(matriz, linhas);

    return 0;
}

void liberarMemoria(int** matriz, int l){
    for(int i=0; i<l; i++){
        free(matriz[i]);
    }
    free(matriz);

    printf("memoria limpa!\n");
}