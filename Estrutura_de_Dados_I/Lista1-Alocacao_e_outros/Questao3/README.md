### 3. Criador de Pontos
**Descrição:** Crie uma função que aloca, preenche e retorna um ponteiro para uma struct `Ponto`.

**Requisitos:**
- Defina uma struct `Ponto` (`int x`, `int y`).
- Crie uma função `Ponto* criarPonto(int x, int y)`.
- Dentro da função, use `malloc` para alocar um `Ponto`.
- Defina os valores `x` e `y` do novo ponto usando o operador seta (`->`).
- A função deve retornar o ponteiro para o `Ponto` alocado.
- Na `main`, chame `Ponto *p1 = criarPonto(10, 5);`.
- Imprima os valores de `p1->x` e `p1->y`.
- Não se esqueça de chamar `free(p1)` na `main`.