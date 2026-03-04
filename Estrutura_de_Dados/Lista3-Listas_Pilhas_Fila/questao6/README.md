### Simulação de Escalonador Round-Robin (CPU)

**Estruturas:** Lista Circular e Fila.
**Cenário:** Simular como um processador divide tempo entre processos.
**Requisitos Técnicos:**

- **Fila de Novos Processos:** Onde chegam processos com `PID` e `TempoTotalNecessario`.
- **Lista Circular (CPU):** Onde os processos rodam.
- **Lógica:**
    1. Mova processos da Fila para a Lista Circular.
    2. A CPU percorre a Lista Circular. Para cada nó, subtraia 2 unidades de tempo (Quantum).
    3. Se o tempo do processo chegar a 0 (ou menos), ele terminou: remova-o da Lista Circular e libere memória.
    4. Se ainda restar tempo, avance para o próximo nó da lista circular.
    5. Repita até que Fila e Lista estejam vazias.