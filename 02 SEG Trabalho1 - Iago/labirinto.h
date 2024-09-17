/*
 * Projeto | AEDS II - Prática
 *
 * Descrição: Projeto para encontrar as coordenadas do caminho entre a entrada e a saída de um labirinto em formato .txt.
 *
 * Nomes: Guilherme Oliveira Araújo    2024.1.08.011
 *        João Antonio Lassister Melo    2024.1.08.027
 *        João Pedro Carvalho Ferreira    2024.1.08.030
 */


#ifndef LABIRINTO_H
#define LABIRINTO_H

// estrutura dos nós da matriz labirinto
typedef struct{
    // campo que guarda o caracter do labirinto na posição
    char chave;
    // campo que guarda a quantidade de caminhos possíveis de serem tomados naquela posição
    int caminhos;
}no_labirinto;
// estrutura de matriz 12x12 de nós com os campos "chave" e "caminhos"
typedef no_labirinto TMatriz[12][12];

// estrutura dos nós da pilha
typedef struct no_ no_pilha;
 struct no_{
    // campo que guarda a coordenada "i"
    int linha;
    // campo que guarda a coordenada "j"
    int coluna;
    // ponteiro que aponta para o próximo nó
    no_pilha *prox;
};

void insere_pilha(no_pilha **topo, no_pilha *novo_no);

void remove_pilha(no_pilha **topo);

void mostra_pilha(no_pilha *topo);

void preenche_bordas(TMatriz labirinto);

void preenche_matriz(TMatriz labirinto, FILE *file, no_pilha *saida);

void move_no_labirinto(TMatriz labirinto, int *i, int *j);

void conta_caminhos(TMatriz labirinto, int i, int j);

void retornar_a_posicao(TMatriz labirinto, no_pilha **topo, int *i, int *j);

#endif