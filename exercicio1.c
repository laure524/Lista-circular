#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    int dados[MAX];
    int inicio;
    int fim;
    int quantidade;
} FilaCircular;

void inicializar(FilaCircular *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int estaCheia(FilaCircular *f) {
    return f->quantidade == MAX;
}

int estaVazia(FilaCircular *f) {
    return f->quantidade == 0;
}

void exibirEstado(FilaCircular *f) {
    printf("[Estado da Fila -> inicio: %d | fim: %d | quantidade: %d/%d]\n",
           f->inicio, f->fim, f->quantidade, MAX);
}

void inserir(FilaCircular *f, int valor) {
    if (estaCheia(f)) {
        printf("\n[ERRO - OVERFLOW] A fila esta cheia! Nao foi possivel inserir %d.\n", valor);
        exibirEstado(f);
        return;
    }

    f->dados[f->fim] = valor;
    printf("\nElemento %d inserido na posicao [%d].\n", valor, f->fim);
    
    // Movimentacao circular utilizando o operador modulo (%)
    f->fim = (f->fim + 1) % MAX;
    f->quantidade++;

    exibirEstado(f);
}

void remover(FilaCircular *f) {
    if (estaVazia(f)) {
        printf("\n[ERRO - UNDERFLOW] A fila esta vazia! Nenhum elemento para remover.\n");
        exibirEstado(f);
        return;
    }

    int removido = f->dados[f->inicio];
    printf("\nElemento %d removido da posicao [%d].\n", removido, f->inicio);

    // Movimentacao circular utilizando o operador modulo (%)
    f->inicio = (f->inicio + 1) % MAX;
    f->quantidade--;

    exibirEstado(f);
}

void listar(FilaCircular *f) {
    if (estaVazia(f)) {
        printf("\nA fila esta vazia.\n");
        exibirEstado(f);
        return;
    }

    printf("\nElementos na fila (ordem FIFO): ");
    int idx = f->inicio;
    for (int i = 0; i < f->quantidade; i++) {
        printf("%d (pos %d)", f->dados[idx], idx);
        if (i < f->quantidade - 1) {
            printf(" -> ");
        }
        idx = (idx + 1) % MAX;
    }
    printf("\n");
    exibirEstado(f);
}

int main() {
    FilaCircular fila;
    inicializar(&fila);

    int opcao, valor;

    do {
        printf("\n==============================\n");
        printf("   FILA CIRCULAR - MENU\n");
        printf("==============================\n");
        printf("1. Inserir elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Listar elementos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // Limpa buffer em caso de entrada invalida
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                printf("Digite o valor inteiro a inserir: ");
                scanf("%d", &valor);
                inserir(&fila, valor);
                break;
            case 2:
                remover(&fila);
                break;
            case 3:
                listar(&fila);
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}