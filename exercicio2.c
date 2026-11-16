#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5
#define TAM_NOME 50

typedef struct {
    int senha;
    char nome[TAM_NOME];
} Pessoa;

typedef struct {
    Pessoa itens[MAX];
    int inicio;
    int fim;
    int quantidade;
} FilaAtendimento;

void inicializar(FilaAtendimento *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int estaCheia(FilaAtendimento *f) {
    return f->quantidade == MAX;
}

int estaVazia(FilaAtendimento *f) {
    return f->quantidade == 0;
}

void exibirEstado(FilaAtendimento *f) {
    printf("[Controle -> inicio: %d | fim: %d | quantidade: %d/%d]\n",
           f->inicio, f->fim, f->quantidade, MAX);
}

void inserirPessoa(FilaAtendimento *f, int senha, const char *nome) {
    if (estaCheia(f)) {
        printf("\n[ERRO - OVERFLOW] Fila de atendimento lotada! Nao foi possivel adicionar %s (Senha %d).\n", nome, senha);
        exibirEstado(f);
        return;
    }

    f->itens[f->fim].senha = senha;
    strncpy(f->itens[f->fim].nome, nome, TAM_NOME - 1);
    f->itens[f->fim].nome[TAM_NOME - 1] = '\0';

    printf("\n[+] Senha %d (%s) adicionada na posicao [%d] do array.\n", senha, nome, f->fim);

    // Avanca o indice fim de forma circular
    f->fim = (f->fim + 1) % MAX;
    f->quantidade++;

    exibirEstado(f);
}

void chamarProxima(FilaAtendimento *f) {
    if (estaVazia(f)) {
        printf("\n[ERRO - UNDERFLOW] Nenhuma pessoa na fila para chamar!\n");
        exibirEstado(f);
        return;
    }

    Pessoa atendida = f->itens[f->inicio];
    printf("\n[>] Chamando senha %d - %s (liberada posicao [%d]).\n",
           atendida.senha, atendida.nome, f->inicio);

    // Avanca o indice inicio de forma circular
    f->inicio = (f->inicio + 1) % MAX;
    f->quantidade--;

    exibirEstado(f);
}

void visualizarFila(FilaAtendimento *f) {
    if (estaVazia(f)) {
        printf("\nA fila de espera esta vazia no momento.\n");
        exibirEstado(f);
        return;
    }

    printf("\n--- FILA DE ESPERA ATUAL ---\n");
    int idx = f->inicio;
    for (int i = 0; i < f->quantidade; i++) {
        printf("%do da fila -> Senha: %d | Nome: %s [indice array: %d]\n",
               i + 1, f->itens[idx].senha, f->itens[idx].nome, idx);
        idx = (idx + 1) % MAX;
    }
    printf("----------------------------\n");
    exibirEstado(f);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    FilaAtendimento fila;
    inicializar(&fila);

    int opcao;
    int contadorSenha = 101; // Gerador automatico de senhas a partir de 101
    char nome[TAM_NOME];

    do {
        printf("\n=====================================\n");
        printf("   SISTEMA DE ATENDIMENTO (FIFO)\n");
        printf("=====================================\n");
        printf("1. Inserir pessoa na fila\n");
        printf("2. Chamar proxima pessoa\n");
        printf("3. Visualizar fila de espera\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = -1;
        } else {
            limparBuffer();
        }

        switch (opcao) {
            case 1:
                printf("Digite o nome da pessoa: ");
                if (fgets(nome, TAM_NOME, stdin) != NULL) {
                    nome[strcspn(nome, "\n")] = '\0'; // Remove o '\n' do final
                    if (strlen(nome) == 0) {
                        strcpy(nome, "Cliente");
                    }
                    inserirPessoa(&fila, contadorSenha, nome);
                    if (!estaCheia(&fila) || fila.quantidade == MAX) {
                        contadorSenha++;
                    }
                }
                break;
            case 2:
                chamarProxima(&fila);
                break;
            case 3:
                visualizarFila(&fila);
                break;
            case 0:
                printf("\nEncerrando sistema de atendimento...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}