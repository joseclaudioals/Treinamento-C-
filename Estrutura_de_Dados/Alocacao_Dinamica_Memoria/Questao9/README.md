### 9. Remoção de Alunos (Shift-Left)
**Descrição:** Adicione ao programa anterior a funcionalidade de "Remover Aluno" por matrícula.

**Requisitos:**
- Adicione a opção "3-Remover" ao menu.
- A função remover deve receber a matrícula.
- Crie uma função `busca(listaAlunos, totalAlunos, matricula)` que retorna o índice do aluno, ou -1 se não encontrar.
- Se encontrado no índice `i`, use a técnica "shift-left": inicie um loop `for` de `j = i` até `totalAlunos - 2` e faça `listaAlunos[j] = listaAlunos[j+1];`.
- Após o loop, decremente `totalAlunos`.