/*
 * Projeto | AEDS II - Prática
 *
 * Descrição: Projeto para encontrar as coordenadas do caminho entre a entrada e a saída de um labirinto em formato .txt.
 *
 * Nomes: Guilherme Oliveira Araújo    2024.1.08.011
 *        João Antonio Lassister Melo    2024.1.08.027
 *        João Pedro Carvalho Ferreira    2024.1.08.030
 */

#include <stdio.h>
#include <stdlib.h>
#include "labirinto.h"

/*
 * Função para inserir nós na pilha.
 */
void insere_pilha(no_pilha **topo, no_pilha *novo_no){
    novo_no->prox = *topo;
    *topo = novo_no;
}

/*
 * Função para remover nós na pilha.
 */
void remove_pilha(no_pilha **topo){
    no_pilha *temp = *topo;
    *topo = (*topo)->prox;
    // desalocação da memória onde se encontra o nó removido da pilha
    free(temp);
}

/*
 * Fução para imprimr o conteúdo da pilha na tela.
 */
void mostra_pilha(no_pilha *topo){
    int i2, j2;
    while (topo != NULL){
        no_pilha *indice = topo;
        // cálculo com os índices para desconsiderar as bordas da matriz e obter a saída desejada
        i2 = indice->coluna - 1;
        j2 = 10 - indice->linha;
        printf("%d,%d\n", i2, j2);
        topo = topo->prox;
        // desalocação da memória onde se encontra o nó cujos dados já foram impressos na tela
        free(indice);
    }
}

/*
 * Função para atribuir "X" às bordas da matriz.
 */
void preenche_bordas(TMatriz labirinto){
    int i, j;
    for (i = 0; i < 12; i++){
        labirinto[i][0].chave = 'X';
    }
    for (i = 0; i < 12; i++){
        labirinto[i][11].chave = 'X';
    }
    for (j = 1; j < 11; j++){
        labirinto[0][j].chave = 'X';
    }
    for (j = 1; j < 11; j++){
        labirinto[11][j].chave = 'X';
    }
}

/*
 * Função para ler o arquivo .txt e preencher a matriz.
 */
void preenche_matriz(TMatriz labirinto, FILE *file, no_pilha *saida){
    int i, j;
    for (i = 1; i < 11; i++){
        for (j = 1; j < 11; j++){
            labirinto[i][j].chave = fgetc(file);
            labirinto[i][j].caminhos = 0;
            // procura das coordenadas da saída
            if (labirinto[i][j].chave == 'S'){
                saida->linha = i;
                saida->coluna = j;
                // atribuição da quatidade máxima de caminhos possíveis de serem tomados a partir da saída
                labirinto[i][j].caminhos = 3;
            }
        }
        // leitura dos "enters" do arquivo fora da matriz
        fgetc(file);
    }
}

/*
 * Função para mover-se para onde não tenha parede.
 */
void move_no_labirinto(TMatriz labirinto, int *i, int *j){
    if (labirinto[*i + 1][*j].chave != 'X'){
            *i += 1;
        }
        else if (labirinto[*i - 1][*j].chave != 'X'){
            *i -= 1;
        }
        else if (labirinto[*i][*j + 1].chave != 'X'){
            *j += 1;
        }
        else if (labirinto[*i][*j - 1].chave != 'X'){
            *j -= 1;
        }
}

/*
 * Função para contabilizar a quatidade de caminhos possíveis de serem tomados a partir daquela posição.
 */
void conta_caminhos(TMatriz labirinto, int i, int j){
    if (labirinto[i + 1][j].chave != 'X'){
        labirinto[i][j].caminhos += 1;
    }
    if (labirinto[i - 1][j].chave != 'X'){
        labirinto[i][j].caminhos += 1;
    }
    if (labirinto[i][j + 1].chave != 'X'){
        labirinto[i][j].caminhos += 1;
    }
    if (labirinto[i][j - 1].chave != 'X'){
        labirinto[i][j].caminhos += 1;
    }
}

/*
 * Função para retirar nós da pilha até retornar a uma posição que tenha mais de 1 caminho possível de ser tomado.
 */
void retornar_a_posicao(TMatriz labirinto, no_pilha **topo, int *i, int *j){
    while (labirinto[(*topo)->linha][(*topo)->coluna].caminhos < 2){
        // atribuição de "X" às posições que levam ao beco
        labirinto[(*topo)->linha][(*topo)->coluna].chave = 'X';
        remove_pilha(topo);
    }
    // atribuição aos índices das novas coordenadas
    *i = (*topo)->linha;
    *j = (*topo)->coluna;
}