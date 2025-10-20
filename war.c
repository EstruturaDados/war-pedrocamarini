// Arquivo: war_nivel_aventureiro.c

#include <stdio.h>    // Para printf, scanf
#include <stdlib.h>   // Para alocação dinâmica (malloc, free) e números aleatórios (rand, srand)
#include <string.h>   // Para manipulação de strings (strcpy)
#include <time.h>     // Para inicializar a semente dos números aleatórios (time)

// A struct 'Territorio' continua a mesma, organizando nossos dados.
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// --- REQUISITO: MODULARIZAÇÃO - Protótipos das Funções ---
// Protótipos são como um "sumário" das nossas funções. Eles informam ao compilador
// quais funções existem, o que elas recebem como parâmetro e o que retornam,
// antes mesmo de implementá-las. Isso nos permite organizar o código de forma mais livre.
void exibirMapa(struct Territorio *mapa, int numTerritorios);
void simularAtaque(struct Territorio *atacante, struct Territorio *defensor);


int main(void) {
    int numTerritorios;

    printf("Bem-vindo ao War Estruturado - Nivel Aventureiro!\n");
    printf("Quantos territorios o seu mundo tera? ");
    scanf("%d", &numTerritorios);

    // --- REQUISITO: ALOCAÇÃO DINÂMICA DE MEMÓRIA ---
    // Em vez de um vetor de tamanho fixo, agora usamos um ponteiro 'mapaMundi'.
    // Um ponteiro é uma variável que "aponta" para um endereço na memória.
    struct Territorio *mapaMundi;

    // A função 'malloc' (memory allocation) reserva um bloco de memória do tamanho que pedirmos.
    // Pedimos espaço para 'numTerritorios' structs 'Territorio'.
    // O ponteiro 'mapaMundi' agora aponta para o início desse bloco, funcionando como nosso vetor.
    mapaMundi = (struct Territorio *) malloc(numTerritorios * sizeof(struct Territorio));

    // Boa prática: Sempre verificar se a alocação de memória deu certo.
    // Se 'malloc' não conseguir memória, ele retorna NULL.
    if (mapaMundi == NULL) {
        printf("Erro: Falha ao alocar memoria para o mapa.\n");
        return 1; // Encerra o programa indicando um erro.
    }

    printf("\nVamos cadastrar os %d territorios do nosso mundo.\n\n", numTerritorios);

    // Laço para cadastrar os territórios, agora com tamanho dinâmico.
    for (int i = 0; i < numTerritorios; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do Territorio: ");
        scanf("%s", mapaMundi[i].nome);
        printf("Cor do Exercito: ");
        scanf("%s", mapaMundi[i].cor);
        printf("Numero de Tropas: ");
        scanf("%d", &mapaMundi[i].tropas);
        printf("\n");
    }

    // --- REQUISITO: GERAÇÃO DE NÚMEROS ALEATÓRIOS ---
    // 'srand(time(NULL))' inicializa o gerador de números aleatórios com base na hora atual.
    // Isso garante que os resultados dos dados sejam diferentes cada vez que o jogo rodar.
    // Fazemos isso apenas UMA VEZ no início do jogo.
    srand(time(NULL));

    int atacanteIdx, defensorIdx;

    // --- REQUISITO: LOOP PRINCIPAL DO JOGO ---
    // Este laço 'do-while' representa os turnos do jogo. Ele continuará rodando
    // até que o jogador decida sair digitando 0.
    do {
        // --- REQUISITO: MODULARIZAÇÃO - Chamada da função exibirMapa ---
        // Em vez de repetir o código de exibição, simplesmente chamamos nossa função especialista.
        exibirMapa(mapaMundi, numTerritorios);

        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", numTerritorios);
        scanf("%d", &atacanteIdx);

        if (atacanteIdx == 0) {
            break; // Sai do laço se o usuário digitar 0.
        }

        printf("Escolha o territorio defensor (1 a %d): ", numTerritorios);
        scanf("%d", &defensorIdx);

        // Validação básica para evitar entradas inválidas
        if (atacanteIdx < 1 || atacanteIdx > numTerritorios || defensorIdx < 1 || defensorIdx > numTerritorios || atacanteIdx == defensorIdx) {
            printf("\nSelecao invalida! Tente novamente.\n");
            continue; // Pula para a próxima iteração do laço.
        }

        // --- REQUISITO: MODULARIZAÇÃO E PONTEIROS - Chamada da função de ataque ---
        // Passamos os endereços de memória (&) dos territórios escolhidos.
        // Isso permite que a função 'simularAtaque' modifique diretamente as tropas
        // e a cor dos territórios originais no nosso 'mapaMundi'.
        simularAtaque(&mapaMundi[atacanteIdx - 1], &mapaMundi[defensorIdx - 1]);

        printf("\nPressione Enter para continuar para o proximo turno...");
        getchar(); // Limpa o buffer de entrada
        getchar(); // Aguarda o Enter

    } while (atacanteIdx != 0);


    // --- REQUISITO: LIBERAÇÃO DE MEMÓRIA ---
    // A função 'free' devolve ao sistema operacional a memória que pegamos emprestada.
    // Isso evita "vazamentos de memória" (memory leaks), uma prática crucial em C.
    free(mapaMundi);

    printf("\nJogo encerrado e memoria liberada. Ate a proxima!\n");

    return 0;
}


// --- REQUISITO: MODULARIZAÇÃO - Implementação da função exibirMapa ---
// Esta função é especialista em uma únca tarefa: mostrar o estado atual do mapa.
// Ela recebe um ponteiro para o mapa e o número de territórios como parâmetros.
void exibirMapa(struct Territorio *mapa, int numTerritorios) {
    printf("\n======================================\n");
    printf("MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("======================================\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
}

// --- REQUISITO: MODULARIZAÇÃO E LÓGICA DE BATALHA - Implementação da função simularAtaque ---
// Esta é a função principal do nível. Ela recebe ponteiros para os territórios
// atacante e defensor, permitindo que ela altere os dados originais.
void simularAtaque(struct Territorio *atacante, struct Territorio *defensor) {
    printf("\n--- RESULTADO DA BATALHA ---\n");

    // Simula o lançamento de um ddo de 6 lados (resultado de 1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    // A seta (->) é usada para acessar campos de uma struct através de um ponteiro.
    // É um atalho para (*atacante).tropas
    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;

        // Verifica se o território foi conquistado
        if (defensor->tropas <= 0) {
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor); // Copia a cor do atacante para o defensor
            defensor->tropas = 1; // O território conquistado fica com 1 tropa
        }
    } else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas--;
    }
}