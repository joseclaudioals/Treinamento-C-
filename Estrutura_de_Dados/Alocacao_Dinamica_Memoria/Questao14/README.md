**Questão 14**
```markdown
### 14. Função alterar (Passando Pessoa **)
**Descrição:** Crie uma função `alterar` que usa `Pessoa **` para garantir que o ponteiro principal seja atualizado se o `realloc` movê-lo de lugar na memória.

**Requisitos:**
- Crie um programa simples (pode ser o Q11) onde `listaAlunos` está na `main`.
- A função de adicionar deve ter o protótipo: `void adicionarAluno(Pessoa ***lista, int *tamanho, int *capacidade);`.
- Na `main`, chame a função passando o endereço do ponteiro: `adicionarAluno(&listaAlunos, &totalAlunos, &capacidade);`.
- Dentro da função, use `*lista` (para acessar o `Pessoa **`) e `**lista` (para