**Questão 18**
```markdown
### 18. Lista Encadeada Simples
**Descrição:** Implemente uma lista encadeada (Linked List) para armazenar inteiros.

**Requisitos:**
- Defina o "nó": `struct No { int valor; struct No *proximo; };`
- Na `main`, crie o ponteiro "cabeça": `struct No *cabeca = NULL;`.
- Implemente `void inserirInicio(struct No **cabeca, int valor);`.
  - Esta função deve receber `struct No **` (ponteiro para ponteiro) para poder modificar a `cabeca`.
  - Dentro, ela deve: `malloc`ar um `novoNo`, definir `novoNo->valor`, definir `novoNo->proximo = *cabeca`, e atualizar a cabeça: `*cabeca = novoNo;`.
- Implemente `void imprimirLista(struct No *cabeca);`.
- Implemente `void liberarLista(struct No **cabeca);`.