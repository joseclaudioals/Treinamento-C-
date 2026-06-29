#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Necessário para o gerador de números aleatórios (srand/rand)

typedef struct NoRadix {
    struct NoRadix *filho[2]; // filho[0] = caminho para bit '0', filho[1] = caminho para bit '1'

    /*
     Trecho de bits que esta aresta/nó representa.
     Na raiz, bits = "" (string vazia), pois a raiz não consome
     nenhum bit, apenas direciona para os filhos.
     */
    char *bits;

    int eh_fim_prefixo; // 1 se o caminho até este nó corresponde a um prefixo válido cadastrado

    char *rota; // Rota associada a este nó, válida apenas quando eh_fim_prefixo == 1
} NoRadix;

char *duplicar_string(const char *origem);
int contar_prefixo_comum(const char *a, const char *b);
NoRadix *criar_no_radix(const char *bits);
void inserir_radix(NoRadix *raiz, const char *prefixo, const char *rota);
const char *buscar_radix(NoRadix *raiz, const char *chave);
void imprimir_radix(NoRadix *no, int profundidade);
int contar_nos_radix(NoRadix *no);
void destruir_radix(NoRadix *no);
void injetar_dados_massa(NoRadix *raiz, int quantidade);

int main(void)
{
    NoRadix *raiz = criar_no_radix(""); // raiz representa o prefixo vazio (não consome nenhum bit)

    printf("=== ETAPA 1: Teste Didatico e Visual ===\n");

    /*
     "1100" e "1101" foram incluídos de propósito: eles
     compartilham o trecho comum "110" e divergem só no último
     bit, o que força a lógica de split a ser exercitada (sem
     eles, os outros 4 prefixos nunca diverge entre si, e o
     split nunca seria testado).
     */
    inserir_radix(raiz, "1",      "Rota 1");
    inserir_radix(raiz, "101",    "Rota 2");
    inserir_radix(raiz, "10110",  "Rota 3");
    inserir_radix(raiz, "101101", "Rota 4");
    inserir_radix(raiz, "1100",   "Rota 5");
    inserir_radix(raiz, "1101",   "Rota 6");

    printf("Estrutura da Arvore Radix apos insercoes manuais:\n");
    imprimir_radix(raiz, 0);
    printf("\nTotal de nos alocados inicialmente: %d\n", contar_nos_radix(raiz));

    // Buscas manuais, para mostrar o Longest Prefix Match funcionando ao vivo
    printf("\n--- Buscas Iniciais ---\n");
    printf("Busca (101101111): %s\n", buscar_radix(raiz, "101101111")); // esperado: Rota 4
    printf("Busca (110011):    %s\n", buscar_radix(raiz, "110011"));    // esperado: Rota 5 (veio do split)
    printf("------------------------\n\n");

    printf("=== ETAPA 2: Teste de Carga (Simulando Core Router) ===\n");

    // inserindo uma alta massa de dados
    // Injeta 100.000 rotas simuladas, com prefixos aleatórios de 8 a 32 bits
    injetar_dados_massa(raiz, 100000);

    printf("Total de nos alocados apos injecao massiva: %d\n", contar_nos_radix(raiz));
    printf("(Numa Trie comum, o consumo de memoria seria absurdamente maior e a arvore muito mais profunda!)\n\n");

    // Testando busca na árvore gigante, depois de 100 mil inserções
    printf("Testando busca em tempo real na arvore gigante...\n");

    printf("Buscando '101101111' -> Encontrou: %s\n", buscar_radix(raiz, "101101111"));

    const char* resultado_nulo = buscar_radix(raiz, "00000000");
    printf("Buscando IP invalido '00000000' -> Encontrou: %s\n",
           resultado_nulo ? resultado_nulo : "Nenhuma rota aplicavel (null)");

    // Libera toda a memória alocada (nós, bits e rotas), incluindo as 100 mil inseridas
    destruir_radix(raiz);

    return 0;
}


/*
 Aloca uma cópia de uma string em memória nova.
 Equivalente a uma strdup() escrita à mão, para não depender
 de extensões não padronizadas do C.
 */
char *duplicar_string(const char *origem)
{
    char *copia = malloc(strlen(origem) + 1); // +1 para o caractere terminador '\0'

    if (!copia) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(copia, origem);
    return copia;
}

/*
 Conta quantos caracteres iniciais são idênticos entre duas
 strings de bits. É a operação central da Árvore Radix: ela
 substitui a comparação "bit a bit contra 1 filho" da trie
 simples por uma comparação "trecho a trecho contra o rótulo
 do nó".

 Exemplo:
 a = "10110"
 b = "1011010"
 retorno = 5 (eles casam em "10110" inteiro)
 */
int contar_prefixo_comum(const char *a, const char *b)
{
    int i = 0;

    // Avança enquanto os caracteres forem iguais e nenhuma das duas strings tiver terminado
    while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i]) {
        i++;
    }

    return i;
}

/*
 Cria um novo nó da Árvore Radix, já armazenando o trecho
 de bits que ele representa. O calloc garante que filho[0],
 filho[1], eh_fim_prefixo e rota comecem zerados/NULL.
 */
NoRadix *criar_no_radix(const char *bits)
{
    NoRadix *no = calloc(1, sizeof(NoRadix));

    if (!no) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    no->bits = duplicar_string(bits);
    return no;
}

/*
 Insere um prefixo binário na Árvore Radix, comprimindo nós
 sempre que possível.

 A lógica percorre a árvore comparando o prefixo que está sendo
 inserido com o "bits" de cada nó. Em cada nó visitado, há 3
 situações possíveis:

 (1) O trecho do nó casa EXATAMENTE com o que falta do prefixo
     novo -> este é o nó certo, apenas marcamos a rota.

 (2) O trecho do nó casa INTEIRO, mas o prefixo novo continua
     além dele -> descemos para o filho indicado pelo próximo
     bit (criando um filho novo se ele não existir).

 (3) O trecho do nó casa só PARCIALMENTE (a divergência ocorre
     no meio do "bits" do nó, ou o prefixo novo termina antes
     do fim do "bits" do nó) -> é preciso "quebrar" o nó em
     dois (split), criando um nó intermediário com o trecho
     comum e dois filhos com os trechos que diferem. É esse
     split que implementa a compressão de fato.
 */
void inserir_radix(NoRadix *raiz, const char *prefixo, const char *rota)
{
    NoRadix *atual = raiz;

    // Ponteiro que avança pelo prefixo conforme ele vai sendo "consumido" pela árvore
    const char *restante = prefixo;

    while (1) {
        int comuns = contar_prefixo_comum(atual->bits, restante);
        int tam_no = strlen(atual->bits);
        int tam_restante = strlen(restante);

        // Caso 1: casamento exato — o trecho do nó é idêntico ao que
        // resta do prefixo. Este é o nó certo para guardar a rota.
        if (comuns == tam_no && comuns == tam_restante) {
            atual->eh_fim_prefixo = 1;

            free(atual->rota); // libera uma rota antiga, se já existia (reinserção do mesmo prefixo)
            atual->rota = duplicar_string(rota);
            return;
        }

        // Caso 2: o nó atual foi todo consumido (seu "bits" inteiro
        // casou), mas o prefixo novo continua além dele. Precisamos
        // descer para o filho indicado pelo próximo bit.

        if (comuns == tam_no) {
            restante += comuns; // avança o "restante" pelo trecho já casado

            int bit = (restante[0] == '1') ? 1 : 0;

            if (!atual->filho[bit]) {
                /*
                 Não existe nada nesse caminho ainda: cria um único
                 nó novo com TODO o restante do prefixo de uma vez.
                 Não criamos 1 nó por bit, como faria a trie simples —
                 essa é a compressão acontecendo na forma mais simples
                 possível de inserção.
                 */
                NoRadix *novo = criar_no_radix(restante);
                novo->eh_fim_prefixo = 1;
                novo->rota = duplicar_string(rota);
                atual->filho[bit] = novo;
                return;
            }

            // Existe um caminho: continua a inserção a partir do filho encontrado
            atual = atual->filho[bit];
            continue;
        }

        /*
         Caso 3: split.

         O casamento parou no MEIO do "bits" do nó atual (ou o
         prefixo novo é mais curto que o "bits" do nó e termina
         dentro dele). Precisamos quebrar este nó em dois.

         Exemplo:
         nó atual tem bits = "100"
         prefixo restante  = "101"
         comuns = 2 (casam em "10")

         Vamos transformar o nó atual para que ele passe a
         representar só o trecho comum "10", e criar dois filhos:
           - um "clone" com o que sobrou do nó antigo ("0"),
             herdando os filhos e a rota que o nó atual já tinha;
           - um nó novo com o que sobrou do prefixo sendo
             inserido ("1").
         */

        // Extrai o trecho comum (vai virar o novo "bits" do nó atual)
        char *trecho_comum = malloc(comuns + 1);
        if (!trecho_comum) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        strncpy(trecho_comum, atual->bits, comuns);
        trecho_comum[comuns] = '\0'; // strncpy não garante o terminador, então fechamos manualmente

        // O que sobra do "bits" antigo, depois do trecho comum
        char *sufixo_antigo = duplicar_string(atual->bits + comuns);

        // O que sobra do prefixo sendo inserido, depois do trecho comum
        char *sufixo_novo = duplicar_string(restante + comuns);

        /*
         Cria o nó "clone", que herda tudo que o nó atual já
         tinha (filhos, marca de fim de prefixo e rota), mas
         agora vive um nível mais abaixo, rotulado com o
         sufixo que sobrou do nó original.
         */
        NoRadix *clone = criar_no_radix(sufixo_antigo);
        clone->filho[0] = atual->filho[0];
        clone->filho[1] = atual->filho[1];
        clone->eh_fim_prefixo = atual->eh_fim_prefixo;
        clone->rota = atual->rota; // transfere a posse da string (não duplica, evita cópia desnecessária)

        // O nó atual agora representa só o trecho comum — "esvaziamos" ele
        free(atual->bits);
        atual->bits = trecho_comum;
        atual->filho[0] = NULL;
        atual->filho[1] = NULL;
        atual->eh_fim_prefixo = 0;
        atual->rota = NULL;

        // Reconecta o clone como filho do nó atual, no bit certo
        int bit_antigo = (sufixo_antigo[0] == '1') ? 1 : 0;
        atual->filho[bit_antigo] = clone;

        if (sufixo_novo[0] == '\0') {
            /*
             O prefixo novo termina exatamente no ponto da divisão:
             o próprio nó "atual" (agora reduzido ao trecho comum)
             passa a ser o fim do prefixo novo.
             */
            atual->eh_fim_prefixo = 1;
            atual->rota = duplicar_string(rota);
        } else {
            // O prefixo novo continua: cria o segundo filho da divisão
            int bit_novo = (sufixo_novo[0] == '1') ? 1 : 0;
            NoRadix *novo = criar_no_radix(sufixo_novo);
            novo->eh_fim_prefixo = 1;
            novo->rota = duplicar_string(rota);
            atual->filho[bit_novo] = novo;
        }

        // Strings temporárias usadas só durante o split: já foram copiadas onde precisavam, podem ir
        free(sufixo_antigo);
        free(sufixo_novo);
        return;
    }
}

/*
 Realiza a busca por Longest Prefix Match na Árvore Radix.

 A ideia é a mesma de uma trie simples (ir guardando a melhor
 rota conforme avança, atualizando sempre que passa por um nó
 que é fim de prefixo válido) — mas aqui a comparação avança um
 TRECHO de bits por vez, não 1 bit por vez.
 */
const char *buscar_radix(NoRadix *raiz, const char *chave)
{
    NoRadix *atual = raiz;
    const char *restante = chave;
    const char *melhor_rota = NULL;

    // A própria raiz pode, em tese, marcar um prefixo válido (rota "default", "")
    if (atual->eh_fim_prefixo)
        melhor_rota = atual->rota;

    while (1) {
        int comuns = contar_prefixo_comum(atual->bits, restante);
        int tam_no = strlen(atual->bits);

        if (comuns < tam_no) {
            /*
             O trecho do nó não casa por completo com a chave:
             a busca não pode continuar por este caminho. Para.
             */
            break;
        }

        // O trecho do nó casou por completo: avança o cursor da chave
        restante += tam_no;

        if (*restante == '\0') {
            // A chave terminou exatamente neste nó
            break;
        }

        int bit = (restante[0] == '1') ? 1 : 0;

        if (!atual->filho[bit])
            break; // Não há caminho a seguir: para aqui

        atual = atual->filho[bit];

        /*
         Sempre que passamos por um nó que marca fim de prefixo,
         atualizamos a melhor rota. Ao final, teremos o prefixo
         válido mais longo (mais específico) que casou com a chave.
         */
        if (atual->eh_fim_prefixo)
            melhor_rota = atual->rota;
    }

    return melhor_rota;
}

/*
 Imprime a estrutura da trie de forma indentada, mostrando o
 "bits" de cada nó. Serve como feedback visual na demonstração:
 dá para ver, ao vivo, os nós comprimidos (cada nó pode ter mais
 de 1 bit no rótulo, diferente de uma trie binária simples).

 Cuidado: só deve ser chamada em árvores pequenas (didáticas),
 */
void imprimir_radix(NoRadix *no, int profundidade)
{
    if (!no)
        return;

    for (int i = 0; i < profundidade; i++)
        printf("  "); // indentação visual proporcional à profundidade do nó

    printf("\"%s\"", no->bits);

    if (no->eh_fim_prefixo)
        printf("  <- rota: %s", no->rota);

    printf("\n");

    // Percorre primeiro o ramo do bit 0, depois o do bit 1 (pré-ordem)
    imprimir_radix(no->filho[0], profundidade + 1);
    imprimir_radix(no->filho[1], profundidade + 1);
}

/*
 Conta quantos nós foram efetivamente alocados na árvore.
 Serve para comparar, na prática, a economia de memória da
 versão comprimida em relação a uma trie binária simples (que
 alocaria 1 nó por bit de cada prefixo, em vez de 1 nó por
 trecho comprimido).
 */
int contar_nos_radix(NoRadix *no)
{
    if (!no)
        return 0;

    return 1 + contar_nos_radix(no->filho[0]) + contar_nos_radix(no->filho[1]);
}

/*
 Libera toda a memória da trie, em pós-ordem: primeiro os
 filhos, depois o próprio nó (incluindo o campo "bits", que
 não existiria numa trie binária simples sem compressão).
 */
void destruir_radix(NoRadix *no)
{
    if (!no)
        return;

    destruir_radix(no->filho[0]);
    destruir_radix(no->filho[1]);

    free(no->bits);
    free(no->rota);
    free(no);
}

/*
 Gera "quantidade" prefixos binários aleatórios (entre 8 e 32
 bits cada, simulando endereços IPv4 fragmentados em sub-redes
 de tamanhos variados) e insere cada um na Árvore Radix.

 Serve para a etapa de "Demonstração" pedida no seminário: em
 vez de inserir só alguns prefixos manuais, isso prova que a
 estrutura aguenta um volume grande de dados (como um roteador
 de núcleo de internet processaria na vida real) sem explodir
 em uso de memória nem ficar lenta.
 */
void injetar_dados_massa(NoRadix *raiz, int quantidade)
{
    printf("\n--- Iniciando injecao de %d rotas em massa ---\n", quantidade);

    /*
     Buffer fixo para montar cada prefixo gerado.
     Tamanho 33 = até 32 bits + 1 posição para o '\0' final.
     Como "tamanho" abaixo nunca passa de 32, prefixo[32] é
     sempre um índice válido (o último do array).
     */
    char prefixo[33];

    // Buffer fixo para montar o nome da rota associada a cada prefixo
    char rota[50];

    /*
     Semente do gerador de números pseudoaleatórios, baseada no
     horário atual. Chamada uma única vez (e não dentro do laço),
     senão poderíamos "resetar" a sequência aleatória a cada
     iteração se o relógio não mudasse entre uma chamada e outra.
     */
    srand(time(NULL));

    for (int i = 0; i < quantidade; i++) {
        /*
         Sorteia um tamanho de prefixo entre 8 e 32 bits.
         rand() % 25 dá um valor de 0 a 24; somando 8, o
         intervalo final fica em 8 a 32.
         */
        int tamanho = (rand() % 25) + 8;

        // Sorteia cada bit do prefixo, um caractere '0' ou '1' por vez
        for (int j = 0; j < tamanho; j++) {
            prefixo[j] = (rand() % 2) ? '1' : '0';
        }
        prefixo[tamanho] = '\0'; // fecha a string no tamanho sorteado

        // Monta um nome de rota único para identificar essa inserção depois
        sprintf(rota, "Rota_Automatica_%d", i + 1);

        // Insere normalmente, usando a mesma função usada nos testes manuais
        inserir_radix(raiz, prefixo, rota);
    }

    printf("Injecao concluida com sucesso!\n");
}

