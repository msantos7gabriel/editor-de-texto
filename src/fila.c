#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "../include/fila.h"

#define TAM_FILA 5
#define MAXIMO_CHAR 80

// Vetor que armazena as linhas copiadas para o clipboard (area de transferencia)
char clipboard[TAM_FILA][MAXIMO_CHAR];

int inicio = 0; // Primeiro elemento da fila
int fim = 0;    // Proxima posicao disponivel para inserir uma linha
int qtd = 0;    // Quantidade atual de elementos armazenados na fila

// Adiciona uma linha no final da fila
void enqueue(char *linha)
{

    strcpy(clipboard[fim], linha);
    fim = (fim + 1) % TAM_FILA;

    // Se a fila não estiver cheia, aumenta a quantidade de elementos
    if (qtd != TAM_FILA)
    {

        qtd++;
    }
    else
    {

        // Se a fila estiver cheia, remove o elemento mais antigo
        inicio = (inicio + 1) % TAM_FILA;
    }
}

// Remove a linha mais antiga da fila e a retorna pelo parâmetro
int dequeue(char *linha)
{

    if (qtd == 0)
    {
        printw("Não há linhas a serem retiradas.\n");
        return 0;
    }
    else
    {
        strcpy(linha, clipboard[inicio]);
        inicio = (inicio + 1) % TAM_FILA;
        qtd--;

        return 1;
    }
}

// Adicione no final de fila.c

void renderizar_fila_lateral(int max_x)
{
    // Define onde a barra lateral vai começar (35 colunas antes do final da tela direita)
    int coluna_inicio = max_x - 35;

    // Só renderiza a barra lateral se a tela for larga o suficiente (evita sobrepor o texto principal)
    if (max_x < 95)
    {
        return;
    }

    // Título da barra lateral
    mvprintw(1, coluna_inicio, "====== ÁREA DE TRANSFERÊNCIA ======");

    if (qtd == 0)
    {
        mvprintw(3, coluna_inicio, "( Vazia )");
    }
    else
    {
        // Percorre a fila e imprime os itens
        for (int i = 0; i < qtd; i++)
        {
            // Calcula a posição do item mais antigo ao mais novo
            int indice_real = (inicio + i) % TAM_FILA;

            // Fazemos uma cópia temporária para remover o \n do final (que o fgets pega)
            char linha_limpa[MAXIMO_CHAR];
            strcpy(linha_limpa, clipboard[indice_real]);
            linha_limpa[strcspn(linha_limpa, "\n")] = '\0'; // Troca o \n por um terminador nulo

            // Imprime limitando a 30 caracteres (%.30s) para não vazar a tela
            mvprintw(3 + i, coluna_inicio, "%d: %.30s", i + 1, linha_limpa);
        }
    }
}