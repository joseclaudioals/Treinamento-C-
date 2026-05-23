#include <stdio.h>
#include <stdlib.h>

typedef struct ItemCompra{
    char nomeCompra[30];
}ItemCompra;

ItemCompra* realocarMemoria(ItemCompra* lista, int* capacidade){
    *capacidade+=3;
    ItemCompra* tempLista = realloc(lista, *capacidade * sizeof(ItemCompra));
    if(tempLista==NULL){
        printf("erro catastrofico! erro ao alocar memoria");
        free(tempLista);
        exit(1);
    }
    return tempLista;
}

int main(void){
    ItemCompra* lista = NULL;
    int total = 0;
    int capacidade=3;
    int opt;

    lista = malloc(sizeof(ItemCompra)*capacidade);
    do{
        if(total==capacidade){
            lista=realocarMemoria(lista, &capacidade);
        }
        
        printf("Insira o nome do Item:\n");
        scanf(" %s", lista[total].nomeCompra);

        printf("Deseja cadastrar outro item?\nSIM [1]\nNAO [2]\n");
        scanf(" %i", &opt);

        total++;
    }while(opt==1);

    for(int i=0; i<total;i++){
        printf("Compra nome: %s\n", lista[i].nomeCompra);
    }

    free(lista);
    return 0;
}