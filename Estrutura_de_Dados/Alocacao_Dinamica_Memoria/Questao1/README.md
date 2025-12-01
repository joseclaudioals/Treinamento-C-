### 1. Cadastro de Veículo
**Descrição:** Crie um programa que aloque dinamicamente a memória para uma única struct `Carro`. O usuário deve preencher os dados, o programa deve exibi-los e, em seguida, liberar a memória.

**Requisitos:**
- Defina uma struct `Carro` (ex: `char modelo[20]`, `char placa[8]`, `int ano`).
- Use `malloc` para alocar espaço para exatamente um `Carro`.
- Verifique se a alocação foi bem-sucedida (`ponteiro != NULL`).
- Use o operador seta (`->`) para preencher os dados da struct via `scanf`.
- Imprima os dados usando o operador seta.
- Use `free` para liberar a memória antes de o programa terminar.