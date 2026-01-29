// Inclusao das bibliotecas padrao necessarias para entrada/saida, alocacao de memoria, manipulacao de strings e tempo.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
// Definem valores fixos para o numero de territorios, missoes e tamanho maximo de strings, facilitando a manutencao.

// --- Estrutura de Dados ---
// Define a estrutura para um territorio, contendo seu nome, a cor do exercito que o domina e o numero de tropas.

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void atacar(Territorio *atacante, Territorio *defensor) {
    // Gerando os dados de 1 a 6 para o atacante e defensor
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d \n", atacante->nome, dadoA);
    printf("O defensor %s rolou um dado e tirou: %d \n", defensor->nome, dadoD);

    if (dadoA >= dadoD) { 
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas -= 1;

        if (defensor->tropas <= 0) {
            strcpy(defensor->cor, atacante->cor);

            // Transfere metade das tropas do atacante para o territorio conquistado
            int metade = atacante->tropas / 2;
            if (metade < 1) metade = 1; 

            atacante->tropas -= metade;
            defensor->tropas = metade;

            printf("CONQUISTA! o territorio %s foi dominado pelo Exercito %s.\n",
                   defensor->nome, defensor->cor);
            printf("Foram movidas %d tropa(s) do atacante para o territorio conquistado.\n", metade);
        } else {
            printf(">>> Defensor perdeu 1 tropa. Tropas do defensor: %d\n", defensor->tropas);
        }
    } else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

// Funcao que libera a memoria alocada do jogo
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

// Funcao que exibe o estado atual do mapa do jogo.
void exibirMapa(Territorio *mapa, int n) {
    printf("\n======================================\n");
    printf("     MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("======================================\n");

    for (int i = 0; i < n; i++) {
        printf("\n%d. %s (Exercito %s, Tropas: %d)",
               i + 1, (mapa + i)->nome, (mapa + i)->cor, (mapa + i)->tropas);
    }

    printf("\n\n======================================\n");
}

int main() {
    srand((unsigned)time(NULL));

    int n;
    printf("\nBem vindo ao WAR! Tenha um bom jogo!\n");
    printf("\nQuantos territorios deseja cadastrar?: ");
    scanf("%d", &n);
    getchar();

    if (n <= 1) {
        printf("O jogo precisa ter ao menos dois territorios!\n");
        return 1;
    }

    Territorio *mapa = (Territorio*)calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("\n============================================\n");
    printf("     WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("============================================\n");

    for (int i = 0; i < n; i++) {
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
    exibirMapa(mapa, n);

    while (1) {
        int a, d;

        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", n);

        scanf("%d", &a);
        getchar();

        if (a == 0) {
            break;
        }

        printf("Escolha o territorio defensor (1 a %d): ", n);
        scanf("%d", &d);
        getchar();

        if (a < 1 || a > n || d < 1 || d > n) {
            printf("Territorio invalido. Use valores entre 1 e %d.\n", n);
            continue;
        }

        if (a == d) {
            printf("Voce nao pode atacar o mesmo territorio!\n");
            continue;
        }

        Territorio *atacante = mapa + (a - 1);
        Territorio *defensor = mapa + (d - 1);

        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("Voce nao pode atacar um territorio da mesma cor!\n");
            continue;
        }

        if (atacante->tropas < 2) {
            printf("Ataque invalido: o atacante precisa ter pelo menos 2 tropas para atacar.\n");
            continue;
        }

        // Executa a batalha
        atacar(atacante, defensor);

        printf("\nPressione Enter para continuar para o proximo turno...");
        getchar(); 

        exibirMapa(mapa, n);
    }

    // Liberacao da memoria antes de encerrar o programa
    liberarMemoria(mapa);
    printf("\nJogo encerrado e memoria liberada. Ate a proxima!\n");
    return 0;
}
