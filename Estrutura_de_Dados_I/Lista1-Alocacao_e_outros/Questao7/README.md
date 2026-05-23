### 7. Vetor Dinâmico Eficiente (O Modelo de Capacidade)
**Descrição:** Refaça o programa anterior, mas desta vez de forma eficiente, usando o conceito de capacidade e total.

**Requisitos:**
- Use duas variáveis: `int totalItens = 0;` e `int capacidade = 4;`.
- Comece alocando a lista com `malloc(capacidade * sizeof(Item))`.
- Ao adicionar um item, verifique se `totalItens == capacidade`.
- Se estiver cheio, dobre a capacidade (`capacidade = capacidade * 2;`) e use `realloc` para expandir o array.
- Adicione o novo item na posição `lista[totalItens]` e incremente `totalItens`.
- Isso evita chamar `realloc` a cada adição.