#include <stdio.h>
#include <stdbool.h>

#define TAM_TAB 10
#define TAM_HAB 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Função para verificar se uma posição está dentro do tabuleiro
bool posValida(int linha, int coluna) {
    return linha >= 0 && linha < TAM_TAB && coluna >= 0 && coluna < TAM_TAB;
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    printf("\n  ");
    for (int i = 0; i < TAM_TAB; i++) {
        printf("%2d", i); // Cabeçalho das colunas
    }
    printf("\n");
    
    for (int i = 0; i < TAM_TAB; i++) {
        printf("%2d", i); // Número da linha
        for (int j = 0; j < TAM_TAB; j++) {
            printf("%2d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para criar matriz de habilidade Cone
void criarCone(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Cone: mais largura conforme desce
            if (j >= i && j < TAM_HAB - i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade Cruz
void criarCruz(int habilidade[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Cruz: linha e coluna central
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade Octaedro
void criarOctaedro(int habilidade[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Octaedro: formato de losango
            int dist = abs(i - centro) + abs(j - centro);
            if (dist <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TAB][TAM_TAB], 
                      int habilidade[TAM_HAB][TAM_HAB], 
                      int centro_linha, int centro_coluna) {
    int offset = TAM_HAB / 2;
    
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int tab_linha = centro_linha - offset + i;
            int tab_coluna = centro_coluna - offset + j;
            
            if (posValida(tab_linha, tab_coluna) && habilidade[i][j] == 1) {
                tabuleiro[tab_linha][tab_coluna] = HABILIDADE;
            }
        }
    }
}

int main() {
    // Inicializa o tabuleiro com água
    int tabuleiro[TAM_TAB][TAM_TAB] = {AGUA};
    
    // Posiciona alguns navios
    tabuleiro[2][3] = NAVIO;
    tabuleiro[2][4] = NAVIO;
    tabuleiro[2][5] = NAVIO;
    tabuleiro[5][7] = NAVIO;
    tabuleiro[6][7] = NAVIO;
    tabuleiro[7][7] = NAVIO;
    
    // Cria e aplica habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];
    
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);
    
    // Aplica habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 3, 4);     // Cone centrado em (3,4)
    aplicarHabilidade(tabuleiro, cruz, 6, 6);     // Cruz centrada em (6,6)
    aplicarHabilidade(tabuleiro, octaedro, 5, 2); // Octaedro centrado em (5,2)
    
    // Exibe o tabuleiro com as habilidades
    printf("=== BATALHA NAVAL COM HABILIDADES ESPECIAIS ===\n");
    printf("Legenda:\n");
    printf("0 - Agua | 3 - Navio | 5 - Area de habilidade\n");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}