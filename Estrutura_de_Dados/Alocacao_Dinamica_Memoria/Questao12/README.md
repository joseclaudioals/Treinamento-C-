### 12. Remoção (Modelo Aluno **)
**Descrição:** Implemente a função de remoção para o modelo `Aluno **`.

**Requisitos:**
- Encontre o índice `i` do aluno a ser removido (usando a função busca).
- **Crucial:** Libere a memória da struct individual: `free(listaAlunos[i]);`.
- Faça o "shift-left" dos ponteiros no array: `listaAlunos[j] = listaAlunos[j+1];`.
- Decremente `totalAlunos`.
- **Opcional:** Defina `listaAlunos[totalAlunos] = NULL;` (o último slot, que agora está duplicado, para segurança).