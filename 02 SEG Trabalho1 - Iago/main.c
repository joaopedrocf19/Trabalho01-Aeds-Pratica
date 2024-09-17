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
#include <string.h>

/*
 * Função principal.
 */
int main(int argc, char *argv[]){
    char caminho_total[30];
    // matriz que receberá o arquivo .txt
    TMatriz labirinto;
    // ponteiro que apontará para o primeiro nó da pilha
    no_pilha *topo = NULL;
    // alocação do nó que receberá as coordenadas da saída do labirinto
    no_pilha *saida = malloc(sizeof(no_pilha));
    if(argc != 2){
        puts("Uso: ./hello <num>");
        return 1;
    }
    // atribuição de "X" às bordas da matriz
    preenche_bordas(labirinto);

    strcpy(caminho_total, "./labirintos/labirinto");
    strcat(caminho_total, argv[1]);
    strcat(caminho_total, ".txt");
    // abertura do arquivo labirindo.txt
    FILE *file = fopen(caminho_total, "r");

    // preenchimento da matriz com os caracteres do arquivo .txt
    preenche_matriz(labirinto, file, saida);

    // fechameto do arquivo labirinto.txt
    fclose(file);

    // inserção do nó com as coordenadas da saída na pilha
    insere_pilha(&topo, saida);

    // índices para percorrer a matriz
    int i, j;
    // for com inicialização dos índices com as coordenadas da saída do labirinto e condição de permanência enquanto a entrada não for encontrada
    for (i = saida->linha, j = saida->coluna; labirinto[i][j].chave != 'E'; ){

        // atribuição de "X" à posição atual
        labirinto[i][j].chave = 'X';

        // movendo-se para onde não tenha parede
        move_no_labirinto(labirinto, &i, &j);

        // alocação de um novo nó para as novas coordenadas
        no_pilha *no_insere = malloc(sizeof(no_pilha));
        no_insere->linha = i;
        no_insere->coluna = j;
        // inserção do nó com as novas coordenadas na pilha
        insere_pilha(&topo, no_insere);

        // contabilização da quatidade de caminhos possíveis de serem tomados a partir daquela posição
        conta_caminhos(labirinto, i, j);

        // verificação para saber se chegou a um beco
        if (labirinto[i][j].caminhos == 0 && labirinto[i][j].chave != 'E'){
            // retorno a uma posição que tenha mais de 1 caminho possível de ser tomado
            retornar_a_posicao(labirinto, &topo, &i, &j);
            // diminuição da quatidade de caminhos possíveis de serem tamados naquela posição
            labirinto[i][j].caminhos -= 1;
        }
    }

    // impressão das coordenadas na tela
    mostra_pilha(topo);

    return 0;
}