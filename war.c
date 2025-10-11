// Arquivo: war_nivel_novato.c

#include <stdio.h>  // Biblioteca para fuções de entrada e saída (printf, scanf).
#include <string.h> // Biblioteca para manipulação de strings (incluída conforme a especificação).

// --- REQUISITO: Definição da struct Territorio ---
// A struct 'Territorio' é um tipo de dado customizado que agrupa informações
// relacionadas a um território do jogo: nome, cor do exército e número de tropas.
// O uso da struct atende aos requisitos de documentação e manutenibilidade,
// organizando os ddos de forma lógica e clara.
struct Territorio {
    char nome[30];  // Campo para o nome, com tamanho 30 conforme especificado.
    char cor[10];   // Campo para a cor, com tamanho 10 conforme especificado.
    int tropas;     // Campo para o número de tropas.
};

int main(void) {
    // --- REQUISITO: Declaração de vetor de structs ---
    // Cria um vetor (array) chamado 'mapaMundi' com capacidade para armazenar
    // 5 estruturas do tipo Territorio. Este vetor representa o mapa do mundo.
    const int NUM_TERRITORIOS = 5;
    struct Territorio mapaMundi[NUM_TERRITORIOS];

    // --- REQUISITO: Usabilidade ---
    // O programa começa com mensagens claras para orientar o usuário sobre o que fazer,
    // garantindo uma boa experiência de uso.
    printf("Vamos cadastrar os %d territorios iniciais do nosso mundo.\n\n", NUM_TERRITORIOS);

    // --- REQUISITO: Entrada dos dados em um laço 'for' ---
    // Este laço de repetição é usado para preencher os dados dos 5 territórios.
    // Ele itera 5 vezes (de i = 0 até 4), uma para cada posição do vetor 'mapaMundi'.
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        // Usa scanf para ler a entrada do usuário e armazená-la no campo 'nome'
        // da struct que está na posição 'i' do vetor.
        scanf("%s", mapaMundi[i].nome);

        printf("Cor do Exercito: ");
        scanf("%s", mapaMundi[i].cor);

        printf("Numero de Tropas: ");
        scanf("%d", &mapaMundi[i].tropas);
        printf("\n");
    }

    printf("Cadastro inicial concluido com sucesso!\n");
    printf("======================================\n");
    printf("MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("======================================\n");

    // --- REQUISITO: Exibição dos dados com formatação clara ---
    // Este segundo laço percorre o vetor 'mapaMundi' que já foi preenchido
    // e exibe os dados de cada território de forma organizada e legível,
    // cumprindo o requisito de exibir as informações após o cadastro.
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\nTERRITORIO %d:\n", i + 1);
        printf(" - Nome: %s\n", mapaMundi[i].nome);
        printf(" - Dominado por: Exercito %s\n", mapaMundi[i].cor);
        printf(" - Tropas: %d\n", mapaMundi[i].tropas);
    }

    return 0;
}