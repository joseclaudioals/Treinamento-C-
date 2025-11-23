#include <stdio.h>
#include <stdlib.h>

int main(void){
    int qntNotas;
    float* diarioNotas;
    float media=0;

    printf("Quantas notas deseja inserir no diário?\n");
    scanf(" %i", &qntNotas);

    diarioNotas = calloc(qntNotas, sizeof(float));
    if(diarioNotas==NULL){
        printf("Erro cadastrofico! Erro ao alocar memoria\n");
        return 1;
    }

    for(int i=0; i<qntNotas; i++){
        printf("Insira a nota do aluno %i\n", i+1);
        scanf(" %f", &diarioNotas[i]);

        media+=diarioNotas[i];
    }
    media/=qntNotas;
    for(int i=0; i<qntNotas; i++){
        printf("Aluno %i: %.2f\n", i+1, diarioNotas[i]);
    }
    printf("Media da turma:%.2f\n", media);
    
    free(diarioNotas);
    diarioNotas=NULL;
    return 0;
}


