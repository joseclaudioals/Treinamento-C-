### O Editor de Texto "Undo/Redo" Limitado

**Estrutura:** Lista Duplamente Encadeada + Ponteiro de Referência.
**Contexto:** Você está criando o *backend* de um editor de texto simples.
**Problema:** O texto é armazenado como uma lista duplamente encadeada de caracteres. Existe um cursor (um ponteiro) que indica a posição atual de edição.
**Requisitos Técnicos:**

- Função `inserirChar(char c)`: Insere onde o cursor está e move o cursor para frente.
- Função `backspace()`: Remove o caractere anterior ao cursor.
- Função `moveCursorLeft()` e `moveCursorRight()`: Navega pela lista.
- **Desafio:** Não use índices (int i), apenas manipulação de ponteiros `proximo` e `anterior`.
- Ao imprimir, mostre o texto e um caractere `|` indicando onde está o cursor.