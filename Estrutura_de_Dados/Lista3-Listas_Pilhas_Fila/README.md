### A Calculadora Polonesa Reversa (RPN) Robusta

**Estrutura:** Pilha Dinâmica.
**Contexto:** Compiladores e calculadoras antigas (HP) utilizam a Notação Polonesa Reversa para processar cálculos sem necessidade de parênteses (ex: `3 4 +` resulta em `7`).
**Problema:** Implemente um avaliador de expressões RPN que suporte as 4 operações básicas (+, -, *, /). O usuário digita uma string longa contendo números e operadores.
**Requisitos Técnicos:**

- A Pilha deve armazenar `float`.
- Deve suportar números com múltiplos dígitos e decimais.
- **Tratamento de Erro:** Se a expressão estiver malformada (ex: `3 +` sem o segundo operando) ou houver divisão por zero, o programa deve limpar a memória, imprimir o erro específico e não travar.
- Ao final, a pilha deve estar vazia (apenas com o resultado).