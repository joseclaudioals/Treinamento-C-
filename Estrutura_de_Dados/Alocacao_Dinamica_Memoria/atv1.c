#include <stdio.h>
#include <ctype.h>

typedef struct Pessoas{
    char nome[25];
    char cpf[12];
    int idade;
}Pessoas;

int main(void){
    Pessoas myPessoas[5];
    int pcount = 0;
    int opt=0;
    do{
        printf("Menu\n");
        printf("cadastrar pessoa ------------ 1\n");
        printf("mostrar uma pessoa ---------- 2\n");
        printf("mostrar todas as pessoas ---- 3\n");
        printf("sair do programa ------------ 4\n");
        scanf(" %i", &opt);
        
        switch(opt){
            case 1: 
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                printf("digite uma opcao valida");
        }
    }while(!(opt>0 && opt<5 ));
}