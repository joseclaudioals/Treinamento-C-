### 17. Struct com Membros Dinâmicos
**Descrição:** Crie um sistema para um "Autor" que pode ter vários "Livros".

**Requisitos:**
- Definições:
  ```c
  struct Livro { char titulo[50]; int ano; };
  struct Autor {
      char nome[50];
      struct Livro *livros; // Array dinâmico de livros
      int totalLivros;
      int capacidadeLivros;
  };