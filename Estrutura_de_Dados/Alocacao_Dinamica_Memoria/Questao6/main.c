#include <stdio.h>
#include <stdlib.h>

typedef struct ItemCompra{
    char nomeCompra[30];
}ItemCompra;

ItemCompra* realocarMemoria(int qntItens, ItemCompra* lista){
    ItemCompra* tempLista = realloc(lista, qntItens * sizeof(ItemCompra));
    if(tempLista==NULL){
        printf("erro catastrofico! erro ao alocar memoria");
        free(tempLista);
        exit(1);
    }
    return tempLista;
}

int main(void){
    ItemCompra* lista = NULL;
    int qntItens = 0;
    int opt;
    do{
        qntItens++;
        
        lista=realocarMemoria(qntItens, lista);

        printf("Insira o nome do Item:\n");
        scanf(" %s", lista[qntItens-1].nomeCompra);

        printf("Deseja cadastrar outro item?\nSIM [1]\nNAO [2]\n");
        scanf(" %i", &opt);

    }while(opt==1);

    for(int i=0; i<qntItens;i++){
        printf("Compra nome: %s\n", lista[i].nomeCompra);
    }

    free(lista);
    return 0;
}