#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// A struct continua a mesma
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// --- NOVO: Variáveis Globais para a Missão ---
// Uso de variáveis globais aqui para que múltiplas funções possam acessá-las facilmente.
int missaoAtual; // Guarda o número da missão sorteada (0 ou 1)
const char *corJogador = "Azul"; // Define a cor do jogador para a missão de conquista
const char *descricoesMissoes[] = { // Um vetor de strings para as descrições
    "Destruir o exercito Verde.",
    "Conquistar 3 territorios."
};


// --- PROTÓTIPOS DAS FUNÇÕES ---
struct Territorio* alocarMapa(int numTerritorios);
void liberarMapa(struct Territorio *mapa);
void inicializarTerritorios(struct Territorio *mapa, int numTerritorios);
void sortearMissao();
void exibirMenu();
void exibirMapa(const struct Territorio *mapa, int numTerritorios);
void jogar(struct Territorio *mapa, int numTerritorios);
int verificarVitoria(const struct Territorio *mapa, int numTerritorios); // NOVO: Agora retorna um int
void simularAtaque(struct Territorio *atacante, struct Territorio *defensor);


int main(void) {
    int numTerritorios;
    struct Territorio *mapaMundi;

    srand(time(NULL));

    printf("Bem-vindo ao War Estruturado - Nivel Mestre!\n");
    printf("Quantos territorios o seu mundo tera? ");
    scanf("%d", &numTerritorios);

    mapaMundi = alocarMapa(numTerritorios);
    if (mapaMundi == NULL) {
        return 1;
    }

    inicializarTerritorios(mapaMundi, numTerritorios);
    sortearMissao();
    jogar(mapaMundi, numTerritorios);
    liberarMapa(mapaMundi);

    printf("\nJogo encerrado. Ate a proxima!\n");
    return 0;
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

struct Territorio* alocarMapa(int numTerritorios) {
    struct Territorio *mapa = (struct Territorio *) malloc(numTerritorios * sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro: Falha ao alocar memoria para o mapa.\n");
    }
    return mapa;
}

void liberarMapa(struct Territorio *mapa) {
    free(mapa);
    printf("Memoria liberada com sucesso.\n");
}

void inicializarTerritorios(struct Territorio *mapa, int numTerritorios) {
    printf("\nVamos cadastrar os %d territorios do nosso mundo.\n\n", numTerritorios);
    for (int i = 0; i < numTerritorios; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do Territorio: ");
        scanf("%s", mapa[i].nome);
        printf("Cor do Exercito: ");
        scanf("%s", mapa[i].cor);
        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

// NOVO: Lógica da função sortearMissao
void sortearMissao() {
    missaoAtual = rand() % 2;

    printf("\n======================================\n");
    printf("SUA MISSAO (Exercito %s): %s\n", corJogador, descricoesMissoes[missaoAtual]);
    printf("======================================\n\n");
}

void exibirMenu() {
    printf("\n--- MENU DE ACOES ---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
    printf("Escolha sua acao: ");
}

void exibirMapa(const struct Territorio *mapa, int numTerritorios) {
    printf("\n--- MAPA DO MUNDO ---\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
}

// NOVO: Para encerrar o jogo ao vencer
void jogar(struct Territorio *mapa, int numTerritorios) {
    int opcao;
    int atacanteIdx, defensorIdx;
    int vitoria = 0; // Flag para controlar o fim do jogo

    do {
        exibirMapa(mapa, numTerritorios);
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n--- FASE DE ATAQUE ---\n");
                printf("Escolha o territorio atacante (1 a %d): ", numTerritorios);
                scanf("%d", &atacanteIdx);
                printf("Escolha o territorio defensor (1 a %d): ", numTerritorios);
                scanf("%d", &defensorIdx);

                if (atacanteIdx < 1 || atacanteIdx > numTerritorios || defensorIdx < 1 || defensorIdx > numTerritorios || atacanteIdx == defensorIdx) {
                    printf("\nSelecao invalida! Tente novamente.\n");
                } else {
                    simularAtaque(&mapa[atacanteIdx - 1], &mapa[defensorIdx - 1]);
                }
                break;
            
            case 2:
                vitoria = verificarVitoria(mapa, numTerritorios);
                if (vitoria) {
                    opcao = 0; // Força a saída do loop se o jogador venceu
                }
                break;

            case 0:
                break;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }
        
        // Se o jogador não venceu nem saiu, aguarda o Enter
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }

    } while (opcao != 0);
}

// NOVO: Lógica da função verificarVitoria
int verificarVitoria(const struct Territorio *mapa, int numTerritorios) {
    switch (missaoAtual) {
        case 0: // Missão: Destruir o exército Verde
            for (int i = 0; i < numTerritorios; i++) {
                if (strcmp(mapa[i].cor, "Verde") == 0) {
                    // Se ainda encontrar um território Verde, a missão não foi cumprida.
                    printf("\nVoce ainda nao cumpriu sua missao. Continue a lutar!\n");
                    return 0; // Retorna 0 (falso)
                }
            }
            // Se o laço terminar e nenhum território Verde foi encontrado...
            printf("\n*** VITORIA! Voce destruiu o exercito Verde e cumpriu sua missao! ***\n");
            return 1; // Retorna 1 (verdadeiro)

        case 1: // Missão: Conquistar 3 territórios
            int territoriosConquistados = 0;
            for (int i = 0; i < numTerritorios; i++) {
                if (strcmp(mapa[i].cor, corJogador) == 0) {
                    territoriosConquistados++;
                }
            }
            if (territoriosConquistados >= 3) {
                printf("\n*** VITORIA! Voce conquistou %d territorios e cumpriu sua missao! ***\n", territoriosConquistados);
                return 1; // Vitória
            } else {
                printf("\nVoce ainda nao cumpriu sua missao. Voce tem %d de 3 territorios. Continue a lutar!\n", territoriosConquistados);
                return 0; // Não venceu ainda
            }
    }
    return 0; // Padrão, caso algo dê errado
}

void simularAtaque(struct Territorio *atacante, struct Territorio *defensor) {
    // Esta função não precisa de nenhuma alteração
    printf("\n--- RESULTADO DA BATALHA ---\n");

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;
        if (defensor->tropas <= 0) {
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
        }
    } else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas--;
    }
}