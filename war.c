// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct Territory {
    char name[50];
    char color[50];
    int troops;
} Territory; 

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.

int numberTerritory();
struct Territory * mapSize(int totalTerritories);

Territory addTerritory();
void showMap(int totalTerritories,Territory map[]);
void createMap(int totalTerritories, Territory map[]);
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    int totalTerritories = numberTerritory();
    struct Territory *map = mapSize(totalTerritories);
    if(map == NULL){
        printf("Falha ao alocar memoria!");
        return 1;
    }
    

    
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    
    createMap(totalTerritories,map);
    
    showMap(totalTerritories, map);
    


    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

int numberTerritory() {
    printf("Digite o numero de territorios: ");
    int totalTerritories;
    scanf("%d", &totalTerritories);
    
    return totalTerritories;
}

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

struct Territory * mapSize(int totalTerritories) {
    
    return (struct Territory *) calloc(totalTerritories, sizeof(struct Territory));
     
}


// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
void createMap(int totalTerritories, Territory map[]) {
    for (int i = 0; i < totalTerritories; i++)
    {
        printf("\n\n--- Cadastrando Territorio %d ---", i + 1);
        map[i] = addTerritory();
    }
} 
// Esta função modifica o mapa passado por referência (ponteiro).
Territory addTerritory() {
    Territory t;

    printf("\n\nDigite o nome do território: ");
    scanf("%s", t.name);

    printf("Digite a cor do território: ");
    scanf("%s", t.color);

    printf("Digite o número de tropas: ");
    scanf("%d", &t.troops);

    printf("\nVocê adicionou:");
    printf("\nTerritório: %s, Controlado por: %s, Total de tropas: %d", t.name, t.color, t.troops);
    return t;
}

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.



// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
void showMap(int totalTerritories,Territory map[]) {
printf("\n\n");
for (int i = 0; i < 50; i++)
{
    printf("=");
}
printf("\n\tMAPA DO MUNDO - ESTADO ATUAL\n");
for (int i = 0; i < 50; i++)
{
    printf("=");
}
printf("\n\n");

for (int i = 0; i < totalTerritories; i++)
    {
        printf("\n\nTERRITORIO %d:\n  - Nome: %s\n  - Controlado por: %s\n  - Tropas: %d",i +1, map[i].name, map[i].color, map[i].troops);
    }
}

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
