### 2. Diário de Notas
**Descrição:** O programa deve perguntar ao usuário quantas notas ele deseja inserir. Em seguida, deve alocar um array dinâmico de `float`s desse tamanho, preenchê-lo e, por fim, calcular e exibir a média das notas.

**Requisitos:**
- Leia um `int N` do usuário.
- Aloque um array de float com `malloc(N * sizeof(float))`.
- Use um loop `for` e a notação de array (`array[i]`) para preencher as notas.
- Calcule a média percorrendo o array.
- Libere a memória com `free`.