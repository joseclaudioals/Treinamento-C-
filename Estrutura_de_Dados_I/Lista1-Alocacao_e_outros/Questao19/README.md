### 19. Lista Encadeada de Structs
**Descrição:** Altere o programa anterior (Q18) para que a lista encadeada armazene ponteiros para `Pessoa`.

**Requisitos:**
- Struct: `struct No { Pessoa *pessoa; struct No *proximo; };`
- A função `inserirInicio` agora deve receber os dados da pessoa.
- Dentro de `inserirInicio`, você deve fazer dois mallocs:
  - `Pessoa *novaPessoa = malloc(sizeof(Pessoa));` (e preencher os dados).
  - `struct No *novoNo = malloc(sizeof(struct No));`.
- Ligar os ponteiros: `novoNo->pessoa = novaPessoa;` e `novoNo->proximo = *cabeca;`.
- A função `liberarLista` deve ser um loop que, a cada passo, chama `free(noAtual->pessoa);` e `free(noAtual);`.