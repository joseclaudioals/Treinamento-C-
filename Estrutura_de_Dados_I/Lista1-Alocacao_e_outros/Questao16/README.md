### 16. Matriz Dinâmica
**Descrição:** Crie um programa que aloca uma matriz (array 2D) de `int`s dinamicamente, com o usuário definindo o número de linhas e colunas.

**Requisitos:**
- Leia `L` (linhas) e `C` (colunas) do usuário.
- Aloque o array de "ponteiros de linha": `int **matriz = malloc(L * sizeof(int *));`.
- Use um loop `for` de `i` de 0 a `L-1`:
  - Dentro do loop, aloque cada linha: `matriz[i] = malloc(C * sizeof(int));`.
- Preencha a matriz (ex: `matriz[i][j] = i + j;`) e depois a imprima.
- Crie uma função `void liberarMatriz(int **matriz, int L)` que usa um loop `for` para `free(matriz[i])` e, no final, chama `free(matriz)`.