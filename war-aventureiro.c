// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.



// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.


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
        printf("VITÓRIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas -= 1;

        if (defensor->tropas <= 0) {
            strcpy(defensor->cor, atacante->cor);

            // Transfere metade das tropas do atacante para o território conquistado
            int metade = atacante->tropas / 2;
            if (metade < 1) metade = 1; 

            atacante->tropas -= metade;
            defensor->tropas = metade;

            printf("CONQUISTA! o territorio %s foi dominado pelo Exército %s.\n", defensor->nome, defensor->cor);
            printf("Foram movidas %d tropa(s) do atacante para o território conquistado.\n", metade);
        } else {
            printf(">>> Defensor perdeu 1 tropa. Tropas do defensor: %d\n", defensor->tropas);
        }
    } else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

// Função que libera a memória alocada do jogo
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

// Função que exibe o estado atual do mapa do jogo.
void exibirMapa(Territorio *mapa, int n) {
    printf("\n======================================\n");
    printf("     MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("======================================\n");

    for (int i = 0; i < n; i++) {
        printf("\n%d. %s (Exército %s, Tropas: %d)",
               i + 1, (mapa + i)->nome, (mapa + i)->cor, (mapa + i)->tropas);
    }

    printf("\n\n======================================\n");
}

int main() {
    srand((unsigned)time(NULL));

    int n;
    printf("\nBem vindo ao WAR! Tenha um bom jogo!\n");
    printf("\nQuantos territórios deseja cadastrar?: ");
    scanf("%d", &n);
    getchar();

    if (n <= 1) {
        printf("O jogo precisa ter ao menos dois territórios!\n");
        return 1;
    }

    Territorio *mapa = (Territorio*)calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("\n============================================\n");
    printf("     WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("============================================\n");

    for (int i = 0; i < n; i++) {
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
    exibirMapa(mapa, n);

    while (1) {
        int a, d;

        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o território atacante (1 a %d, ou 0 para sair): ", n);

        scanf("%d", &a);
        getchar();


        if (a == 0) {
            break;
        }


        printf("Escolha o território defensor (1 a %d): ", n);
        scanf("%d", &d);
        getchar();

        if (a < 1 || a > n || d < 1 || d > n) {
            printf("Território inválido. Use valores entre 1 e %d.\n", n);
            continue;
        }

        if (a == d) {
            printf("Você não pode atacar o mesmo território!\n");
            continue;
        }

        Territorio *atacante = mapa + (a - 1);
        Territorio *defensor = mapa + (d - 1);

        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("Você não pode atacar um território da mesma cor!\n");
            continue;
        }

        if (atacante->tropas < 2) {
            printf("Ataque inválido: o atacante precisa ter pelo menos 2 tropas para atacar.\n");
            continue;
        }

        // Executa a batalha
        atacar(atacante, defensor);

        printf("\nPressione Enter para continuar para o próximo turno...");
        getchar(); 

        exibirMapa(mapa, n);
    }

    // Liberação da memória antes de encerrar o programa
    liberarMemoria(mapa);
    printf("\nJogo encerrado e memória liberada. Até a próxima!\n");
    return 0;
}
