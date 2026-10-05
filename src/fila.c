#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "../include/fila.h"

#define TAM_FILA 5
#define MAXIMO_CHAR 80

char clipboard[TAM_FILA][MAXIMO_CHAR];

int inicio = 0;
int fim = 0;
int qtd = 0;

void enqueue(char *linha)
{

    strcpy(clipboard[fim], linha);
    fim = (fim + 1) % TAM_FILA;

    if (qtd != TAM_FILA)
    {

        qtd++;
    }
    else
    {

        inicio = (inicio + 1) % TAM_FILA;
    }
}

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

void renderizar_fila_lateral(int max_x)
{

    int coluna_inicio = max_x - 35;

    if (max_x < 95)
    {
        return;
    }

    mvprintw(1, coluna_inicio, "====== ÁREA DE TRANSFERÊNCIA ======");

    if (qtd == 0)
    {
        mvprintw(3, coluna_inicio, "( Vazia )");
    }
    else
    {

        for (int i = 0; i < qtd; i++)
        {

            int indice_real = (inicio + i) % TAM_FILA;

            char linha_limpa[MAXIMO_CHAR];
            strcpy(linha_limpa, clipboard[indice_real]);
            linha_limpa[strcspn(linha_limpa, "\n")] = '\0';

            mvprintw(3 + i, coluna_inicio, "%d: %.30s", i + 1, linha_limpa);
        }
    }
}