#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ------------------ Funcoes utilitarias ------------------

int contarTerritoriosDaCor(Territorio *mapa, int n, const char *cor) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        // strcmp retorna 0 quando as strings sao iguais
        if (strcmp(mapa[i].cor, cor) == 0) count++;
    }
    return count;
}


int somarTropasDaCor(Territorio *mapa, int n, const char *cor) {
    int soma = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(mapa[i].cor, cor) == 0) soma += mapa[i].tropas;
    }
    return soma;
}


int existeCorNoMapa(Territorio *mapa, int n, const char *cor) {
    for (int i = 0; i < n; i++) {
        if (strcmp(mapa[i].cor, cor) == 0) return 1;
    }
    return 0;
}


void listarCoresDisponiveis(Territorio *mapa, int n) {
    printf("\nCores disponiveis no mapa:\n");

    for (int i = 0; i < n; i++) {
        int jaMostrou = 0;

        // Verifica se a cor do territorio i ja apareceu em algum territorio anterior
        for (int j = 0; j < i; j++) {
            if (strcmp(mapa[i].cor, mapa[j].cor) == 0) {
                jaMostrou = 1;
                break;
            }
        }

        if (!jaMostrou) {
            printf("- %s\n", mapa[i].cor);
        }
    }
}

int coletarCoresUnicas(Territorio *mapa, int n, char cores[][10], int maxCores) {
    int total = 0;

    for (int i = 0; i < n; i++) {
        int repetida = 0;

        for (int j = 0; j < total; j++) {
            if (strcmp(mapa[i].cor, cores[j]) == 0) {
                repetida = 1;
                break;
            }
        }

        if (!repetida) {
            if (total < maxCores) {
                strcpy(cores[total], mapa[i].cor);
                total++;
            }
        }
    }
    return total;
}

int sortearCorInimiga(Territorio *mapa, int n, const char *corJogador, char *corAlvo) {
    // Primeiro pega todas as cores unicas do mapa
    char cores[50][10];
    int total = coletarCoresUnicas(mapa, n, cores, 50);

    // Depois filtra apenas as cores que nao sao a do jogador
    char inimigas[50][10];
    int totalInimigas = 0;

    for (int i = 0; i < total; i++) {
        if (strcmp(cores[i], corJogador) != 0) {
            strcpy(inimigas[totalInimigas], cores[i]);
            totalInimigas++;
        }
    }

    if (totalInimigas == 0) return 0;

    int idx = rand() % totalInimigas;
    strcpy(corAlvo, inimigas[idx]);
    return 1;
}

// ------------------ Missoes ------------------

void atribuirMissao(char *destino, const char *missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

int verificarMissao(char *missao, Territorio *mapa, int tamanho,
                    const char *corJogador, int territoriosIniciais,
                    const char *corAlvo) {

    // Conta quantos territorios atualmente pertencem ao jogador
    int meusTerritorios = contarTerritoriosDaCor(mapa, tamanho, corJogador);

    if (strcmp(missao, "Conquistar mais 2 territorios (alem dos que voce ja tem).") == 0) {
        return (meusTerritorios >= territoriosIniciais + 2);
    }

    char missaoElim[200];
    snprintf(missaoElim, sizeof(missaoElim),
             "Eliminar todas as tropas do exercito %s.", corAlvo);

    if (strcmp(missao, missaoElim) == 0) {
        return !existeCorNoMapa(mapa, tamanho, corAlvo);
    }

    return 0;
}

// ------------------ Jogo ------------------

void atacar(Territorio *atacante, Territorio *defensor) {
    // Dados de 1 a 6
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou e tirou: %d\n", atacante->nome, dadoA);
    printf("O defensor %s rolou e tirou: %d\n", defensor->nome, dadoD);

    if (dadoA >= dadoD) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas -= 1;

        // Se o defensor ficou sem tropas, o atacante conquista o territorio
        if (defensor->tropas <= 0) {
            // Troca a cor do territorio para a cor do atacante
            strcpy(defensor->cor, atacante->cor);

            // Move metade das tropas do atacante para o territorio conquistado
            int metade = atacante->tropas / 2;
            if (metade < 1) metade = 1;

            atacante->tropas -= metade;
            defensor->tropas = metade;

            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s.\n",
                   defensor->nome, defensor->cor);
            printf("Foram movidas %d tropa(s) para o territorio conquistado.\n", metade);
        } else {
            // Se nao conquistou, so mostra quantas tropas sobraram
            printf("Defensor agora tem %d tropa(s).\n", defensor->tropas);
        }
    } else {
        // Defensor venceu a rodada
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

void exibirMapa(Territorio *mapa, int n) {
    printf("\n=============== MAPA DO MUNDO ===============\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s (Exercito: %s, Tropas: %d)\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("=============================================\n");
}

void exibirMissao(const char *missao, const char *corJogador) {
    printf("\n--- SUA MISSAO (Exercito %s) ---\n", corJogador);
    printf("%s\n", missao);
}

void exibirMenu(void) {
    printf("\n--- MENU DE ACOES ---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
    printf("Escolha sua acao: ");
}


void liberarMemoria(Territorio *mapa, char *missaoJogador) {
    free(mapa);
    free(missaoJogador);
}

int main() {
    // Inicializa a semente do randomico (rand) usando o tempo atual
    srand((unsigned)time(NULL));

    int n;

    // Entrada: numero de territorios
    printf("\nBem-vindo ao WAR! Tenha um bom jogo!\n");
    printf("Quantos territorios deseja cadastrar?: ");
    scanf("%d", &n);
    getchar();

    // Validacao simples
    if (n <= 1) {
        printf("O jogo precisa ter ao menos dois territorios!\n");
        return 1;
    }

    // Aloca dinamicamente um vetor de territorios (mapa)
    Territorio *mapa = (Territorio*)calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memoria para o mapa.\n");
        return 1;
    }

    // Cadastro inicial do mapa
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

        if (mapa[i].tropas < 0) mapa[i].tropas = 0;
    }

    printf("\nCadastro inicial concluido!\n");
    exibirMapa(mapa, n);

    // O jogador escolhe uma cor valida (que existe no mapa)
    char corJogador[10];

    listarCoresDisponiveis(mapa, n);

    do {
        printf("\nEscolha a cor do SEU exercito: ");
        scanf("%9s", corJogador);
        getchar();

        if (!existeCorNoMapa(mapa, n, corJogador)) {
            printf("Cor invalida. Escolha uma das cores listadas acima.\n");
        }
    } while (!existeCorNoMapa(mapa, n, corJogador));

    // Guarda quantos territorios o jogador tinha no inicio
    int territoriosIniciais = contarTerritoriosDaCor(mapa, n, corJogador);

    // Lista de missoes
    const char *missoes[] = {
        "Conquistar mais 2 territorios (alem dos que voce ja tem)."
    };
    int totalMissoes = (int)(sizeof(missoes) / sizeof(missoes[0]));

    // Cor alvo para missao dinamica de eliminar
    char corAlvo[10] = "";

    char *missaoJogador = (char*)malloc(200);
    if (!missaoJogador) {
        printf("Erro ao alocar memoria para a missao.\n");
        free(mapa);
        return 1;
    }

    int temCorInimiga = sortearCorInimiga(mapa, n, corJogador, corAlvo);

    if (temCorInimiga && (rand() % 2 == 0)) {
        snprintf(missaoJogador, 200, "Eliminar todas as tropas do exercito %s.", corAlvo);
    } else {
        atribuirMissao(missaoJogador, missoes, totalMissoes);
    }

    exibirMissao(missaoJogador, corJogador);

    // Loop principal do jogo (turnos)
    while (1) {
        int opcao;

        exibirMapa(mapa, n);
        exibirMissao(missaoJogador, corJogador);
        exibirMenu();

        scanf("%d", &opcao);
        getchar();

        if (opcao == 0) break;

        if (opcao == 1) {
            int a, d;

            printf("\n--- FASE DE ATAQUE ---\n");
            printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", n);
            scanf("%d", &a);
            getchar();

            // 0 sai do loop (encerra o jogo)
            if (a == 0) break;

            printf("Escolha o territorio defensor (1 a %d): ", n);
            scanf("%d", &d);
            getchar();

            // Validacoes basicas dos indices escolhidos
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

            // Nao pode atacar um territorio da mesma cor
            if (strcmp(atacante->cor, defensor->cor) == 0) {
                printf("Voce nao pode atacar um territorio da mesma cor!\n");
                continue;
            }

            if (atacante->tropas < 2) {
                printf("Ataque invalido: o atacante precisa ter pelo menos 2 tropas.\n");
                continue;
            }

            atacar(atacante, defensor);

            printf("\nPressione Enter para continuar para o proximo turno...");
            getchar();

        } else if (opcao == 2) {
            if (verificarMissao(missaoJogador, mapa, n, corJogador, territoriosIniciais, corAlvo)) {
                printf("\nVITORIA! Voce cumpriu sua missao!\n");
                break;
            } else {
                printf("\nVoce ainda nao cumpriu a sua missao. Continue a lutar!\n");
            }

            printf("\nPressione Enter para continuar...");
            getchar();

        } else {
            printf("Opcao invalida.\n");
        }
    }

    liberarMemoria(mapa, missaoJogador);
    printf("\nJogo encerrado e memoria liberada. Ate a proxima!\n");
    return 0;
}
