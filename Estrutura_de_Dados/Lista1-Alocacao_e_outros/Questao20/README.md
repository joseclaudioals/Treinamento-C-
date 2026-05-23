### 20. Desafio Final: Ponteiros para Funções (Polimorfismo em C)
**Descrição:** Crie um array de "Formas" (Círculos e Quadrados) e calcule a área de cada uma, mesmo sem saber o tipo delas, usando ponteiros para funções.

**Requisitos:**
- Defina `struct Circulo { float raio; };` e `struct Quadrado { float lado; };`.
- Defina os protótipos das funções: `float areaCirculo(void *forma);` e `float areaQuadrado(void *forma);`.
- Crie uma struct `FormaGenerica` que contenha:
  - `int tipo;` (1=Circulo, 2=Quadrado)
  - `void *dados;` (um ponteiro genérico)
  - `float (*calcularArea)(void *dados);` (um ponteiro para função)
- Na `main`, crie um array dinâmico de `FormaGenerica`: `FormaGenerica **lista = ...;`
- Ao adicionar um círculo:
  - `Circulo *c = malloc(sizeof(Circulo)); c->raio = 5;`
  - `lista[i] = malloc(sizeof(FormaGenerica));`
  - `lista[i]->tipo = 1;`
  - `lista[i]->dados = c;`
  - `lista[i]->calcularArea = areaCirculo;` (atribui a função)
- No final, percorra o array `lista` e imprima: `float area = lista[i]->calcularArea(lista[i]->dados);`.