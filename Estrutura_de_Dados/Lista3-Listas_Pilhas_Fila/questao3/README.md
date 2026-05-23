### Gerenciador de Playlist de Músicas sem Repetição

**Estrutura Principal:** Lista Encadeada Simples.
**Cenário:** Um aplicativo de música precisa gerenciar uma playlist. O diferencial é que ele não pode permitir músicas duplicadas e deve permitir reordenar músicas.
**Requisitos Técnicos:**

- Struct `Musica` contendo `ID` (int) e `Titulo` (string).
- Função `adicionar(Musica m)`: Antes de inserir no final da lista, percorra a lista para verificar se o ID já existe. Se existir, retorne erro.
- Função `trocarPosicao(int id1, int id2)`: Localize dois nós pelo ID e troque o **conteúdo** deles (ou os ponteiros, para um desafio maior) de lugar.
- Garanta que não haja vazamento de memória ao remover uma música.