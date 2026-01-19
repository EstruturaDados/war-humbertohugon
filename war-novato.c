// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

#include <stdio.h>
#include <string.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

#define TERRITORIOS 5

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.


typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[TERRITORIOS];

    printf("\nVamos cadastrar os 5 territórios iniciais do nosso mundo.\n");

    for (int i = 0; i < TERRITORIOS; i++) {
        printf("\n--- Cadastrando Território %d ---\n", i + 1);

        printf("Nome do Território: ");
        scanf("%29[^\n]", mapa[i].nome);
        getchar();

        printf("Cor do Exército (ex: Azul, Verde): ");
        scanf("%9s", mapa[i].cor);
        getchar();

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }

    printf("\nCadastro Inicial concluído com sucesso!\n");

    // Exebir os territórios cadastrados
    printf("\n======================================\n");
    printf("     MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("======================================\n");

    for (int i = 0; i < TERRITORIOS; i++) {
        printf("\nTERRITÓRIO %d:\n", i + 1);
        printf("- Nome: %s\n", mapa[i].nome);
        printf("- Dominado por: Exército %s\n", mapa[i].cor);
        printf("- Tropas: %d\n", mapa[i].tropas);
    }

    printf("\n=================================\n");

    return 0;
}
