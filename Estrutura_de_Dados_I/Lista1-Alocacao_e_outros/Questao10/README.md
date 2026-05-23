### 10. Otimização de Memória (Shrink-to-Fit)
**Descrição:** Adicione uma funcionalidade ao programa de Alunos (Q9) que otimiza o uso da memória.

**Requisitos:**
- Adicione a opção "4-Otimizar Memória" ao menu.
- A função otimizar deve verificar se `capacidade > totalAlunos`.
- Se for verdade, ela deve chamar `realloc` para encolher o array, definindo a nova capacidade exatamente igual a `totalAlunos`.
  - `listaAlunos = realloc(listaAlunos, totalAlunos * sizeof(Aluno));`
  - `capacidade = totalAlunos;`
- Isso testa o uso de `realloc` para diminuir a memória.