#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// --- CONFIGURAÇÃO DE TEMPO (CROSS-PLATFORM) ---
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(x) Sleep(x)
#else
    #include <unistd.h>
    #define SLEEP_MS(x) usleep(x * 1000) // usleep usa microsegundos
#endif

void delay_visual(int ms) {
    fflush(stdout); // FORÇA o texto a aparecer antes de dormir
    SLEEP_MS(ms);
}

// --- DEFINIÇÕES DO SISTEMA ---
#define NUM_CLUSTERS 32
#define CLUSTER_SIZE 512
#define FAT_FREE 0x00000000
#define FAT_EOF  0x0FFFFFFF
#define MAX_FILES 16

// --- ESTRUTURAS ---
typedef struct {
    char nome[12];
    uint32_t tamanho;
    uint32_t primeiro_cluster;
    bool ocupado;
} DirectoryEntry;

typedef struct {
    uint32_t FAT[NUM_CLUSTERS];
    char data_blocks[NUM_CLUSTERS][64];
    DirectoryEntry root_dir[MAX_FILES];
} VirtualDisk;

VirtualDisk disco;

// --- FUNÇÕES AUXILIARES ---

void formatarDisco() {
    printf("[BIOS] Detectando hardware...\n"); delay_visual(500);
    printf("[SISTEMA] Formatando disco FAT32");
    
    for (int i = 0; i < 3; i++) { printf("."); delay_visual(400); } // Efeito de carregamento
    printf("\n");

    for (int i = 0; i < NUM_CLUSTERS; i++) {
        disco.FAT[i] = FAT_FREE;
        strcpy(disco.data_blocks[i], "");
    }
    disco.FAT[0] = 0xFFFFFFF8;
    disco.FAT[1] = 0xFFFFFFFF;
    
    for (int i = 0; i < MAX_FILES; i++) {
        disco.root_dir[i].ocupado = false;
    }
    printf("[SISTEMA] Formatacao concluida. %d Clusters disponiveis.\n\n", NUM_CLUSTERS - 2);
    delay_visual(1000);
}

int encontrarClusterLivre() {
    // Simula o tempo de busca na tabela
    delay_visual(100); 
    for (int i = 2; i < NUM_CLUSTERS; i++) {
        if (disco.FAT[i] == FAT_FREE) {
            return i;
        }
    }
    return -1;
}

void mostrarTabelaFAT() {
    printf("\n");
    printf("   [VISUALIZADOR DA FAT NA RAM]\n");
    printf("   ----------------------------\n");
    for (int i = 2; i < NUM_CLUSTERS; i++) {
        if (disco.FAT[i] != FAT_FREE) {
            char valor[15];
            if (disco.FAT[i] == FAT_EOF) sprintf(valor, "[EOF]");
            else sprintf(valor, "-> %02d", disco.FAT[i]);
            
            printf("   CLUSTER %02d | Map: %-7s | Dados: %s\n", i, valor, disco.data_blocks[i]);
            delay_visual(50); // Efeito cascata na listagem
        }
    }
    printf("   ----------------------------\n\n");
    delay_visual(1000);
}

// --- OPERAÇÕES COM VISUALIZAÇÃO ---

void criarArquivo(const char* nome, int numero_clusters, const char* conteudo_simulado) {
    printf("[WRITE] Iniciando gravacao de: '%s'\n", nome);
    delay_visual(500);

    int dir_idx = -1;
    for (int i = 0; i < MAX_FILES; i++) {
        if (!disco.root_dir[i].ocupado) { dir_idx = i; break; }
    }
    
    if (dir_idx == -1) return;

    int cluster_anterior = -1;
    int primeiro_cluster = -1;

    for (int k = 0; k < numero_clusters; k++) {
        printf("   ... Buscando espaco livre na FAT... ");
        int atual = encontrarClusterLivre();
        
        if (atual == -1) { printf("ERRO: Disco cheio!\n"); return; }
        
        printf("Encontrado Cluster %d.\n", atual);
        delay_visual(400); // Simula cálculo

        disco.FAT[atual] = FAT_EOF;
        
        printf("   ... Gravando dados magneticos no setor %d... ", atual);
        snprintf(disco.data_blocks[atual], 60, "%s (Pt %d)", conteudo_simulado, k+1);
        delay_visual(600); // Simula tempo de escrita física (Write Latency)
        printf("[OK]\n");

        if (cluster_anterior != -1) {
            printf("   ... Atualizando FAT: Cluster %d agora aponta para %d.\n", cluster_anterior, atual);
            disco.FAT[cluster_anterior] = atual;
            delay_visual(300);
        } else {
            primeiro_cluster = atual;
        }
        
        cluster_anterior = atual;
        printf("\n");
    }

    strcpy(disco.root_dir[dir_idx].nome, nome);
    disco.root_dir[dir_idx].tamanho = numero_clusters * CLUSTER_SIZE;
    disco.root_dir[dir_idx].primeiro_cluster = primeiro_cluster;
    disco.root_dir[dir_idx].ocupado = true;
    
    printf("[WRITE] Arquivo '%s' fechado e salvo no Diretorio Raiz.\n", nome);
    printf("---------------------------------------------------\n");
    delay_visual(1500);
}

void lerArquivo(const char* nome) {
    printf("\n[READ] Solicitacao de leitura: '%s'\n", nome);
    delay_visual(800);
    
    int start_cluster = -1;
    // Simula busca linear no diretório
    for (int i = 0; i < MAX_FILES; i++) {
        if (disco.root_dir[i].ocupado && strcmp(disco.root_dir[i].nome, nome) == 0) {
            start_cluster = disco.root_dir[i].primeiro_cluster;
            break;
        }
    }

    if (start_cluster == -1) { printf("   Erro 404: Arquivo nao encontrado.\n"); return; }

    int atual = start_cluster;
    printf("   -> Arquivo encontrado iniciando no Cluster %d\n", atual);
    delay_visual(500);

    while (atual != FAT_EOF && atual != FAT_FREE) {
        printf("   [CABEÇOTE] Lendo Cluster %02d... ", atual);
        delay_visual(700); // Simula o tempo de leitura e rotação do disco
        printf("BUFFER: \"%s\"\n", disco.data_blocks[atual]);
        
        int proximo = disco.FAT[atual];
        
        printf("   [FAT] Consultando tabela... ");
        delay_visual(300);
        
        if (proximo == FAT_EOF) {
            printf("Resultado: FIM DO ARQUIVO (EOF).\n");
            break;
        } else {
            printf("Resultado: O proximo pedaco esta no Cluster %d.\n", proximo);
            printf("   ... Movendo cabecote ...\n");
            delay_visual(400); // Seek time
            atual = proximo;
        }
    }
    printf("[READ] Leitura concluida com sucesso.\n");
    printf("---------------------------------------------------\n");
    delay_visual(1500);
}

void deletarArquivo(const char* nome) {
    printf("\n[DELETE] Solicitacao de exclusao: '%s'\n", nome);
    delay_visual(500);
    
    int dir_idx = -1;
    for (int i = 0; i < MAX_FILES; i++) {
        if (disco.root_dir[i].ocupado && strcmp(disco.root_dir[i].nome, nome) == 0) {
            dir_idx = i;
            break;
        }
    }

    if (dir_idx == -1) return;

    int atual = disco.root_dir[dir_idx].primeiro_cluster;
    printf("   -> Iniciando limpeza da cadeia FAT a partir do Cluster %d\n", atual);
    
    while (atual != FAT_EOF && atual != FAT_FREE) {
        int proximo = disco.FAT[atual];
        
        printf("   ... Formatando Cluster %d (Zerando bit)... ", atual);
        disco.FAT[atual] = FAT_FREE;
        strcpy(disco.data_blocks[atual], "[LIVRE]"); 
        delay_visual(300); // Tempo de deleção
        printf("[OK]\n");
        
        atual = proximo;
    }

    disco.root_dir[dir_idx].ocupado = false;
    printf("[DELETE] Arquivo removido do indice.\n");
    printf("---------------------------------------------------\n");
    delay_visual(1000);
}

// --- MAIN ---

int main() {
    formatarDisco();

    // Cenário: Gravar arquivos
    criarArquivo("AGENTE.MP4", 4, "VIDEO: Cena 01"); // Ocupa clusters 2,3,4,5
    
    criarArquivo("GTA_SA.ISO", 3, "GAME: Loading");   // Ocupa clusters 6,7,8
    
    criarArquivo("RHCP.MP3", 2, "AUDIO: Intro");      // Ocupa clusters 9,10

    // Mostrar estado atual
    mostrarTabelaFAT();

    // Ler o filme
    lerArquivo("AGENTE.MP4");

    // Simular fragmentação: Deletar o arquivo do MEIO
    deletarArquivo("GTA_SA.ISO"); // Libera clusters 6,7,8

    // Gravar algo novo para ver ocupando o buraco
    printf("\n[USUARIO] Gravando novo arquivo (BLACK.ISO) para testar fragmentacao...\n");
    delay_visual(2000);
    
    criarArquivo("BLACK.ISO", 3, "GAME: Tiroteio"); 
    // O sistema deve reusar os clusters 6,7,8 automaticamente

    mostrarTabelaFAT();

    return 0;
}