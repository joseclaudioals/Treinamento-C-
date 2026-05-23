### 8. Cadastro de Alunos (Modelo Aluno *)
**Descrição:** Crie um sistema de cadastro de alunos (struct `Aluno` com `int matricula`, `char nome[50]`) usando o modelo de capacidade do exercício 7.

**Requisitos:**
- Use um ponteiro `Aluno *listaAlunos = NULL;`, `int totalAlunos = 0;`, `int capacidade = 2;`.
- Crie um menu (1-Adicionar, 2-Listar, 0-Sair).
- **Adicionar:** Verifica se `totalAlunos == capacidade`. Se sim, chama uma função `alocar()` (que usa `realloc` para dobrar a capacidade). Em seguida, pede os dados do aluno e os armazena em `listaAlunos[totalAlunos]`, e incremente `totalAlunos`.
- **Listar:** Percorre o array de 0 até `totalAlunos` e imprime os dados.
- **Sair:** Libera a memória com `free(listaAlunos)`.