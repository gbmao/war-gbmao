// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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
#define STRING_SIZE 50
#define TOTAL_MISSIONS 5
// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct Territory {
    char name[STRING_SIZE];
    char color[STRING_SIZE];
    int troops;
} Territory; 

typedef struct Player {
    char color[STRING_SIZE];
    struct Territory *maps;
    int currentSize;
    int missionID;

} Player;

typedef struct Mission {
    int missionID;
    char missionDescription[STRING_SIZE];
} Mission;

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.

int numberTerritory();
struct Territory * mapSize();

Territory addTerritory();
void showMap();
void createMap();
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
int createGame();

void choseColor();
void showMenu();
int attackMenu();
// Funções de lógica principal do jogo:
void attack(int attacker,int defender);
int checkMission();
// Função utilitária:
void clearInput();
int totalTerritories;
struct Territory *map;


void createMockMap();

void addAllTerritoriesWithSameColorToPlayer();
void addTerritoryToPlayer(int location);
Player createPlayer(Mission missions[]);

Player p ;
struct Mission* missions;

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    srand(time(NULL));
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
     if(createGame() == 1) return 1;

    showMenu();
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
    free(map);
    free(p.maps);
    free(missions);
    return 0;
}

// --- Implementação das Funções ---

struct Mission * createMissions() {
   // (struct Territory *) calloc(totalTerritories, sizeof(struct Territory));
     struct Mission* missions =  malloc(TOTAL_MISSIONS * sizeof(struct Mission));
     // criando manualmente as missoes
     missions[0].missionID = 1; 
     strcpy(missions[0].missionDescription, "Domine 3 Territorios");

     missions[1].missionID = 2; 
     strcpy(missions[1].missionDescription, "Domine 2 Territorios");

     missions[2].missionID = 3; 
     strcpy(missions[2].missionDescription, "Destrua exercito azul");

     missions[3].missionID = 4; 
     strcpy(missions[3].missionDescription, "Destrua exercito amarelo");

     missions[4].missionID = 5; 
     strcpy(missions[4].missionDescription, "Destrua exercito verde");

     return missions;

} 

Player createPlayer( Mission missions[]) {
    
    Player p;
    p.currentSize = 0;
    p.maps = NULL;
    p.color[0] = '\0';   
    // TODO melhorar sistema de missao
    p.missionID = rand() % TOTAL_MISSIONS;
    
    return p;
}

int checkMission() {
    if (p.missionID == 0) {
        
        if(p.currentSize >= 3) {
            
            printf("\n --- VITORIA ---\n");
            printf("\n VOCE DOMINOU 3 TERRITORIOS\n");
            return 1;
        }

    } else if (p.missionID == 1) {

        if(p.currentSize >= 2) {
            printf("\n --- VITORIA ---\n");
            printf("\n VOCE DOMINOU 2 TERRITORIOS\n");
            return 1;
        }
        return 0;
    } else if (p.missionID == 2) {
        
        for (int i = 0; i < totalTerritories; i++)
        {
            if(strcmp(map[i].color, "azul") == 0) {
                return 0;
            }
        }
        printf("\n --- VITORIA ---\n");
        printf("\n VOCE DESTRUIU EXERCITO AZUL\n");
        
        return 1;
        
    } else if (p.missionID == 3) {
        
        for (int i = 0; i < totalTerritories; i++)
        {
            if(strcmp(map[i].color, "amarelo") == 0) {
                return 0;
            }
        }
        printf("\n --- VITORIA ---\n");
        printf("\n VOCE DESTRUIU EXERCITO AMARELO\n");
        
        return 1;
        
    } else if (p.missionID == 4) {
        
        for (int i = 0; i < totalTerritories; i++)
        {
            if(strcmp(map[i].color, "verde") == 0) {
                return 0;
            }
        }
        printf("\n --- VITORIA ---\n");
        printf("\n VOCE DESTRUIU EXERCITO VERDE\n");
        
        return 1;
        
    }
    return 0; // missão não cumprida
}

int numberTerritory() {
    int totalTerritories;
    printf("Digite o numero de territorios: ");
    scanf("%d", &totalTerritories);
    clearInput();
    
    return totalTerritories;
}

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

struct Territory * mapSize() {
    
    return (struct Territory *) calloc(totalTerritories, sizeof(struct Territory));
     
}

int createGame(){

    totalTerritories = numberTerritory();
    map = mapSize();
    if(map == NULL){
        printf("Falha ao alocar memoria!");
        return 1;
    }

    createMap();
     missions  = createMissions();
    p = createPlayer(missions); 
    
   // createMockMap();
    choseColor();
    return 0;
}
// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
void createMap() {
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
    clearInput();

    printf("Digite a cor do território: ");
    scanf("%s", t.color);
    clearInput();

    printf("Digite o número de tropas: ");
    scanf("%d", &t.troops);
    clearInput();

    printf("\nVocê adicionou:");
    printf("\nTerritório: %s, Controlado por: %s, Total de tropas: %d", t.name, t.color, t.troops);
    return t;
}

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.


void choseColor() {
    printf("\n---- ESCOLHA SUA COR ----\n");
    for (int i = 0; i < totalTerritories; i++)
    {
        printf("%d. %s\n",i+1, map[i].color);
    }

    printf("Sua escolha: \n");

    int response;
    scanf("%d", &response);

    
    strcpy(p.color, map[response -1].color);

    printf("p.color: %s\n", p.color);

    // addTerritoryToPlayer(response -1);

    // printf("p.map: %s\n", p.maps[0].color);
    // printf("p.map: %d\n", p.maps[0].troops);

    addAllTerritoriesWithSameColorToPlayer();

    // for (int i = 0; i < p.currentSize; i++)
    // {
    //     printf("p.map: %s\n", p.maps[i].name);
    // }
}

void addAllTerritoriesWithSameColorToPlayer() {

    for(int i = 0; i < totalTerritories; i++){
        if(strcmp(p.color, map[i].color) == 0){
            printf("p.color : %s == map.color: %s\n", p.color, map[i].color);
            addTerritoryToPlayer(i);
        }
    } 
}

void addTerritoryToPlayer(int location){
    p.currentSize++;
    p.maps = realloc(p.maps, (p.currentSize) * sizeof(Territory));
    if(p.maps ==  NULL){
        printf("Nao alocou memoria\n");
    }

    p.maps[p.currentSize -1] = map[location];
    
}

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

void showMenu(){
    
    int flag = 1;
    int response;
    do {

    showMap( totalTerritories, map);
    printf("\n\n------ MISSAO -------\n");
    printf("%s.\n", missions[p.missionID].missionDescription);
    printf("\n --- MENU DE ACOES --- \n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("3 - Verificar Map\n");
    printf("0 - Sair\n");
    scanf("%d", &response);
    clearInput();

    switch (response)
    {
    case 0:
        printf("Saindo...\n");
        flag = 0;
        break;

    case 1:
        flag = attackMenu(totalTerritories, map);
        break;
    
    case 2:
        printf("\n\n------ MISSAO -------\n");
        printf("%s.\n", missions[p.missionID].missionDescription);
        printf("\nPressione ENTER para voltar ao menu...\n\n");
        getchar();
        break;

    case 3:
        showMap( totalTerritories, map);
        printf("\nPressione ENTER para voltar ao menu...\n\n");
        getchar();
        break;
    default:
        break;
    }
    
    if(checkMission()) {
        printf("\nPressione ENTER para terminar o jogo...\n\n");
        getchar();
        flag = 0;
    }

    }while (flag);
    
}



// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
void showMap() {
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
printf("\n");

for (int i = 0; i < totalTerritories; i++)
    {
        printf("%d.%s (Exercito: %s, Tropas: %d)\n",i +1, map[i].name, map[i].color, map[i].troops);
    }

for (int i = 0; i < 50; i++)
{
    printf("=");
}
}


// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

int attackMenu() {
    int flag = 1;
    printf("\n\n----- FASE DE ATAQUE -----\n");
    int attacking;
    int defense;

    do {

    printf("Escolha o territorio atacante(1 a %d, ou 0 para SAIR): ", totalTerritories);
    scanf("%d", &attacking);
    clearInput();
    if(attacking == 0) return 0;
        if(map[attacking-1].troops < 2) {
            printf("\n%s possui apenas %d tropa e não pode atacar!\n", map[attacking-1].name, map[attacking-1].troops);
        } else {
            flag = 0;
        }
    } while(flag);
    flag = 1;
    do {
    printf("Escolha o territorio defensor(1 a %d): ", totalTerritories);
    scanf("%d", &defense);
    clearInput();
        if(defense == attacking) {
            printf("Voce nao pode escolher o mesmo territorio! escolha novamente\n ");
            flag = 1;
        } else if(strcmp(map[attacking-1].color, map[defense -1].color) == 0){
            printf("\nO territorio defensor possui a mesma cor do atacante!\n");
        } else {
            flag = 0;
        }
    }while(flag);

    attack(attacking -1,defense -1);
    printf("\nPressione ENTER para continuar para o proximo turno...\n\n");
    getchar();
    return 1;
    
}

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.
void attack(int attacker, int defender){

    int num = (rand() % 6) + 1;
    printf("\nO atacante %s rolou um dado e tirou: %d", map[attacker].name, num);
    int num2 = (rand() % 6) + 1;
    printf("\nO defensor %s rolou um dado e tirou: %d", map[defender].name, num2);

    if(num > num2) { // attack wins
        num = num - num2;
        printf("\nVITORIA DO ATAQUE! O defensor perdeu %d", num);
        map[defender].troops -= num;
        if(map[defender].troops < 1) {
            printf("\nCONQUISTA! O territorio %s foi dominado pelo exercito %s", map[defender].name, map[attacker].color);
            //map[defender].color = map[attacker].color;
            strcpy(map[defender].color, map[attacker].color);
            map[defender].troops = 1;
            addTerritoryToPlayer(defender);
            
        }
    
    } else if (num < num2) {
        num = num2 - num;
        printf("\nVITORIA DA DEFESA! O atacante perdeu 1 tropa");
        map[attacker].troops -= 1;
    } else {
        printf("\nEmpate ninguem perde tropas\n");
    }
}

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// clearInput():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void clearInput() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}


void createMockMap() {
    totalTerritories = 5; // define quantos territórios
    map = mapSize();
    if (map == NULL) {
        printf("Falha ao alocar memoria!");
        exit(1);
    }

    strcpy(map[0].name, "Brasil");
    strcpy(map[0].color, "Vermelho");
    map[0].troops = 5;

    strcpy(map[1].name, "Argentina");
    strcpy(map[1].color, "Azul");
    map[1].troops = 3;

    strcpy(map[2].name, "Chile");
    strcpy(map[2].color, "Vermelho");
    map[2].troops = 4;

    strcpy(map[3].name, "Peru");
    strcpy(map[3].color, "Azul");
    map[3].troops = 2;

    strcpy(map[4].name, "Colombia");
    strcpy(map[4].color, "Vermelho");
    map[4].troops = 6;
}

