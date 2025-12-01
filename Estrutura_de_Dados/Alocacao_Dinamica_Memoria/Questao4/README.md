### 4. Estoque Fixo
**Descrição:** Aloque dinamicamente um array para 5 struct `Produto` (ex: `char nome[30]`, `float preco`, `int quantidade`). O usuário deve preencher os dados dos 5 produtos.

**Requisitos:**
- Use `malloc` para alocar o bloco de memória para 5 structs.
- Use um loop `for` para pedir ao usuário que preencha os dados de cada produto.
- Use a notação de array (`estoque[i].nome = ...`) para acessar os membros.
- Após o preenchimento, use outro loop `for` para imprimir todos os produtos.
- Libere o único bloco de memória alocado com `free`.