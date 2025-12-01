### 11. Cadastro Básico (Modelo Aluno **)
**Descrição:** Recrie o programa de cadastro (Q8), mas desta vez usando um "array de ponteiros para structs".

**Requisitos:**
- A variável global (ou da main) deve ser `Aluno **listaAlunos = NULL;`.
- Ao iniciar, aloque o array de ponteiros: `listaAlunos = malloc(capacidade * sizeof(Aluno *));`.
- **Adicionar:**
  - Verifique a capacidade (como no Q8). Se estiver cheia, `realloc` o array de ponteiros (`listaAlunos`).
  - **Crucial:** Aloque memória para a nova struct: `listaAlunos[totalAlunos] = malloc(sizeof(Aluno));`.
  - Peça os dados e os armazene usando o operador seta: `listaAlunos[totalAlunos]->matricula = ...`.
  - Incremente `totalAlunos`.
- **Listar:** Use o operador seta para imprimir: `printf("%s", listaAlunos[i]->nome);`.
- **Sair:** Requer um loop para `free(listaAlunos[i])` em cada aluno, e depois um `free(listaAlunos)` para o array de ponteiros.