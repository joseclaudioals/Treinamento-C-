/*Crie um programa que declare três variáveis: int, float e char. Para cada variável, declare um ponteiro correspondente. Associe cada ponteiro ao endereço de sua respectiva variável. Por fim, imprima uma tabela mostrando, para cada variável, seu valor (acesso direto), seu endereço de memória (usando o operador &) e seu valor novamente (desta vez, acessado através do ponteiro).*/

#include <stdio.h>

int main(void){
    //definindo variaveis
    int a=1;
    float b=1.2;
    char c='a';
    //passando o endereço das variáveis para o ponteiro correspondente
    int* ap = &a;
    float* bp = &b;
    char* cp = &c;
    //verificando o endereço e o valor de cada variável e o valor acessado pelo ponteiro
    
    printf("endereco da variavel a = %p | valor da variavel = %d | valor do ponteiro ap = %d\n", &a, a, *ap);
    printf("endereco da variavel b = %p | valor da variavel = %.1f | valor do ponteiro bp = %.1f\n", &b, b, *bp);
    printf("endereco da variavel c = %p | valor da variavel = %c | valor do ponteiro cp = %c\n", &c, c, *cp);

    
    return 0;
}