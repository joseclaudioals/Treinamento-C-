/*
    Escreva uma função que calcula a soma de todos os elementos de uma matriz 3x4. A função deve receber apenas um ponteiro para o primeiro elemento da matriz (int *) e as dimensões (número de linhas e colunas).
*/

#include <stdio.h>

int somarElementos(int *matriz, int linhas, int colunas);

int main(void){
    int matriz [3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    int somaTotal = 0;

    somaTotal = somarElementos(&matriz[0][0], sizeof(matriz)/sizeof(matriz[0]), sizeof(matriz[0])/sizeof(matriz[0][0]));

    printf("a soma de todos elementos da matriz eh: %i\n", somaTotal);

    return 0;
}

int somarElementos(int *matriz, int linhas, int colunas){
    int somatotal=0;
    for(int i = 0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            somatotal += *(matriz+(i*colunas)+j);
        }
    }

    return somatotal;
}
