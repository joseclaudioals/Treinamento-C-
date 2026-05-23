### 6. Lista de Compras Simples
**Descrição:** Crie um programa que permita ao usuário adicionar itens (structs `Item` com `char nome[30]`) a uma lista, um de cada vez, indefinidamente.

**Requisitos:**
- Comece com `Item *lista = NULL;` e `int tamanho = 0;`.
- Em um loop, pergunte o nome do item.
- A cada novo item, aumente `tamanho` e use `realloc` para aumentar o bloco de memória para `tamanho * sizeof(Item)`.
- Adicione o novo item na posição `lista[tamanho - 1]`.
- O loop para quando o usuário digita "sair".
- No final, imprima todos os itens e libere a memória. (Este método é ineficiente, mas é um bom primeiro passo com `realloc`).