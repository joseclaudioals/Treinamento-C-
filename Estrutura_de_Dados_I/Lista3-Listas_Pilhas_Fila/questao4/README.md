### Roteador de Atendimento (Call Center)

**Estrutura Principal:** Fila Dinâmica.
**Cenário:** Um sistema recebe chamadas de clientes e as coloca em espera.
**Requisitos Técnicos:**

- Implemente uma **Fila** onde cada nó representa um `Cliente` (contendo `Nome` e `NumeroProtocolo`).
- O sistema deve gerar o `NumeroProtocolo` automaticamente (incremental) a cada inserção.
- Função `atenderProximo()`: Remove o primeiro da fila e imprime "Atendendo [Nome] - Protocolo [X]".
- Função `furarFila(char* nome)`: Um caso especial para emergências. Insere um cliente diretamente no **início** da estrutura (note: filas normais não permitem isso, você terá que adaptar sua lógica de ponteiros `head`).