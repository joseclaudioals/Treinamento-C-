### 5. Função de Cópia
**Descrição:** Crie uma struct `Retangulo` (`float largura`, `float altura`). Escreva uma função que receba um ponteiro para um `Retangulo` e retorne um ponteiro para uma nova cópia alocada dinamicamente.

**Requisitos:**
- Protótipo da função: `Retangulo* copiarRetangulo(Retangulo *original);`.
- Dentro da função, aloque memória para um novo `Retangulo`.
- Copie os valores (largura e altura) do original para a cópia.
- Retorne o ponteiro para a cópia.
- Na `main`, crie e preencha um retângulo, chame `copiarRetangulo`, e depois libere a memória dos dois retângulos.