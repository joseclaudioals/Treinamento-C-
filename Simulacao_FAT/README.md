# 🗄️ Simulador de Sistema de Arquivos FAT32

Este projeto é uma implementação em **C** que simula as operações de baixo nível de um sistema de arquivos inspirado no FAT32. O objetivo é visualizar como o sistema operacional gerencia o espaço em disco, organiza arquivos em clusters e lida com a fragmentação.

## 🚀 Funcionalidades

- **Formatação de Disco:** Inicializa a tabela FAT e o diretório raiz.
- **Escrita de Arquivos:** Aloca clusters dinamicamente para novos dados.
- **Leitura Sequencial:** Segue a "corrente" (chain) de clusters na FAT para reconstruir o arquivo.
- **Deleção de Arquivos:** Libera os clusters na tabela FAT para novos usos.
- **Simulação de Latência:** Inclui efeitos visuais que simulam o tempo de busca (*seek time*) e gravação magnética.
- **Visualização de Fragmentação:** Demonstra como novos arquivos ocupam espaços deixados por arquivos deletados.

## 🏗️ Estrutura do Sistema

O simulador utiliza as seguintes estruturas de dados:

- **FAT (Tabela de Alocação):** Um array de inteiros onde cada índice aponta para o próximo pedaço do arquivo ou indica o fim (`EOF`).
- **Data Blocks:** Uma representação simplificada dos setores físicos onde o conteúdo é armazenado.
- **Directory Entry:** Um registro que armazena o nome do arquivo, tamanho e, crucialmente, o **primeiro cluster** do arquivo.

## 🛠️ Como Compilar e Executar

O código é multiplataforma e pode ser compilado em Windows ou Linux.

### No Windows (GCC/MinGW):

Bash

`gcc simulador_fat.c -o simulador.exe
./simulador.exe`

### No Linux:

Bash

`gcc simulador_fat.c -o simulador
./simulador`

## 📊 Exemplo de Fluxo

1. O sistema é formatado.
2. Um arquivo `AGENTE.MP4` é criado ocupando 4 clusters.
3. Um arquivo `GTA_SA.ISO` é criado logo em seguida.
4. Ao deletar o `GTA_SA.ISO`, os clusters intermediários ficam livres.
5. Ao gravar um novo arquivo, o sistema demonstra inteligência ao preencher os "buracos" deixados na tabela FAT, ilustrando como a fragmentação acontece no mundo real.

## 📝 Notas de Implementação

- **Ponteiros Virtuais:** O valor `0xFFFFFFFF` é usado para representar o fim de um arquivo (EOF).
- **Cross-Platform:** O código utiliza macros `#ifdef _WIN32` para garantir que o tempo de espera (*sleep*) funcione corretamente em diferentes sistemas operacionais.