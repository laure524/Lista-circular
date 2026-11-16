# Lista-circular
# Fila Circular em C

Autora: Lauren Tavares  
Disciplina: Estrutura de dados  

Descrição dos Exercícios
Este repositório contém a implementação prática de estruturas de dados do tipo *Fila Circular* (FIFO — First In, First Out) em linguagem C, utilizando arrays estáticos, `struct` e aritmética modular (`%`) para reaproveitamento de memória.

**`exercicio1.c`**: Implementação de uma fila circular de números inteiros com menu interativo para inserção, remoção e listagem dos elementos, exibindo os índices `inicio`, `fim` e `quantidade` a cada operação.
**`exercicio2.c`**: Simulação de um sistema de fila de atendimento onde cada elemento é uma `struct` contendo o número da senha e o nome da pessoa, com controle de *overflow* (fila cheia), *underflow* (fila vazia) e reaproveitamento circular dos índices.

# Instruções de Compilação e Execução
Certifique-se de ter o compilador `gcc` instalado. No terminal, dentro da pasta do projeto, execute:

### Exercício 1
```bash
gcc exercicio1.c -o exercicio1
./exercicio1
