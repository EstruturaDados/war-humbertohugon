// Inclusao das bibliotecas padrao necessarias para entrada/saida, alocacao de memoria, manipulacao de strings e tempo.

#include <stdio.h>
#include <string.h>

// --- Constantes Globais ---
// Definem valores fixos para o numero de territorios, missoes e tamanho maximo de strings, facilitando a manutencao.

#define TERRITORIOS 5

// --- Estrutura de Dados ---
// Define a estrutura para um territorio, contendo seu nome, a cor do exercito que o domina e o numero de tropas.


typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[TERRITORIOS];

    printf("\nVamos cadastrar os 5 territorios iniciais do nosso mundo.\n");

    for (int i = 0; i < TERRITORIOS; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        scanf("%29[^\n]", mapa[i].nome);
        getchar();

        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf("%9s", mapa[i].cor);
        getchar();

        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }

    printf("\nCadastro Inicial concluido com sucesso!\n");

    // Exebir os territorios cadastrados
    printf("\n======================================\n");
    printf("     MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("======================================\n");

    for (int i = 0; i < TERRITORIOS; i++) {
        printf("\nTERRITORIO %d:\n", i + 1);
        printf("- Nome: %s\n", mapa[i].nome);
        printf("- Dominado por: Exercito %s\n", mapa[i].cor);
        printf("- Tropas: %d\n", mapa[i].tropas);
    }

    printf("\n=================================\n");

    return 0;
}
